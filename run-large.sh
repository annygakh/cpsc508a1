for i in {1..100}
do
  echo "iteration $i"
  ./large $(uname)

  # uncomment below for NILFS2
  nilfs-clean -p 1 /dev/loop14
  sleep 10
done