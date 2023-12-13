PARAMS = -g -W

build: fileOperations dataOperations checks tableOperations rowOperations 
	gcc ./src/main.c ./output/fileOperations.o ./output/dataOperations.o ./output/checks.o ./output/tableOperations.o ./output/rowOperations.o -o SGBD $(PARAMS)

test: fileOperations checks tableOperations dataOperations rowOperations
	gcc ./tests/teste.c ./output/fileOperations.o ./output/dataOperations.o ./output/checks.o ./output/tableOperations.o ./output/rowOperations.o -o ./tests/teste $(PARAMS)

	
fileOperations:
	gcc ./src/fileOperations.c -o ./output/fileOperations.o -c $(PARAMS)
dataOperations:
	gcc ./src/dataOperations.c -o ./output/dataOperations.o -c $(PARAMS)
checks:
	gcc ./src/checks.c -o ./output/checks.o -c $(PARAMS)
tableOperations:
	gcc ./src/tableOperations.c -o ./output/tableOperations.o -c $(PARAMS)
rowOperations:
	gcc ./src/rowOperations.c -o ./output/rowOperations.o -c $(PARAMS)

clean:
	rm -f ./output/*.o

cleanTest:
	rm -f ./output/*.o ./tests/teste