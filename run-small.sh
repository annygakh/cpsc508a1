for i in {1..100}
do
  echo "iteration $i"
  ./small $(uname)

  # uncomment below for NILFS2
  if ! (($i % 5)); then
    nilfs-clean -p 1 /dev/loop14
    sleep 10
  fi
done