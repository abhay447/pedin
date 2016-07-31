for i in {40..400..40};do
	./startSim.sh $i >temp;
	tail -n1 temp >>obstacle.csv;
done;
