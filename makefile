PARAMS = -g -W

build: database fileOperations dataOperations tableChecks tableOperations rowOperations 
	gcc ./src/main.c ./output/database.o ./output/fileOperations.o ./output/dataOperations.o ./output/tableChecks.o ./output/tableOperations.o ./output/rowOperations.o -o SGBD $(PARAMS)

test: database fileOperations tableChecks tableOperations dataOperations
	gcc ./tests/teste.c ./output/database.o ./output/fileOperations.o ./output/dataOperations.o ./output/tableChecks.o ./output/tableOperations.o -o ./tests/teste $(PARAMS)

database:  
	gcc ./src/database.c -o ./output/database.o -c $(PARAMS)
fileOperations:
	gcc ./src/fileOperations.c -o ./output/fileOperations.o -c $(PARAMS)
dataOperations:
	gcc ./src/dataOperations.c -o ./output/dataOperations.o -c $(PARAMS)
tableChecks:
	gcc ./src/tableChecks.c -o ./output/tableChecks.o -c $(PARAMS)
tableOperations:
	gcc ./src/tableOperations.c -o ./output/tableOperations.o -c $(PARAMS)
rowOperations:
	gcc ./src/rowOperations.c -o ./output/rowOperations.o -c $(PARAMS)

cleanBuild:
	rm -f ./output/*.o SGBD

cleanTest:
	rm -f ./output/*.o teste