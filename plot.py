import plotly.offline as offline
import plotly.graph_objs as go
import csv


def chart_data(filename):
  data = {}
  with open(filename, 'r') as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
      operation = row[0]
      platform = row[1]
      time = row[2]
      if platform not in data:
        data[platform] = {"operation" : [], "time": []}
      data[platform]["operation"].append(operation)
      data[platform]["time"].append(DIVIDE / float(time))
  return data

def scatter_data(filename):
  data = {}
  with open(filename, 'r') as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
      operation = row[0]
      platform = row[1]
      time = row[2]
      if platform not in data:
        data[platform] = {}
      if operation not in data[platform]:
        data[platform][operation] = []
      data[platform][operation].append(DIVIDE / float(time))
  return data

def plot_scatter(dataset):
  for platform in dataset:
    traces = []
    max_size = 0
    for operation in dataset[platform]:
      max_size = len(dataset[platform][operation])
      trace = go.Scatter(
        x = range(0, max_size),
        y = dataset[platform][operation],
        mode = 'markers',
        name = operation
      )
      traces.append(trace)
    layout = go.Layout(
      xaxis = dict(range=[0,max_size]),
      yaxis = dict(range=[0.0, 1.0]),
    )
    fig = go.Figure(data=traces, layout=layout)
    offline.plot(traces, filename = platform)

def plot_chart(dataset, layout, fname):
  traces = []
  for platform in dataset:
    trace = go.Bar(
      x=dataset[platform]["operation"],
      y=dataset[platform]["time"],
      name=platform,
    )
    traces.append(trace)
  fig = go.Figure(data=traces, layout = layout)
  offline.plot(fig, filename=fname)


if __name__ == "__main__":
  # large benchmarks
  DIVIDE = 10000
  fname = "benchmarks_large.all.csv"
  chart_layout = go.Layout(
    title = 'Large-file performance under NILFS2 and ext3',
    yaxis=dict(
      title='kilobytes/sec'
    ),
  )
  plot_chart(chart_data(fname), chart_layout, "benchmarks_large.html")
  plot_scatter(scatter_data(fname))

  # small benchmarks
  DIVIDE = 10000
  fname = "benchmarks_small.all.csv"
  chart_layout = go.Layout(
    title = 'Small-file performance under NILFS2 and ext3',
    xaxis=dict(
      title='10000 1K file access'
    ),
    yaxis=dict(
      title='Files/sec'
    ),
    barmode='group'
  )
  plot_chart(chart_data(fname), chart_layout, "benchmarks_small.html")
  plot_scatter(scatter_data(fname))

