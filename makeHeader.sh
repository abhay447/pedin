cd forceStats;
files=$(ls);
for file in $files;do
	sed -i  '1s/^/time,active,passive,force \n/' $file
done;

