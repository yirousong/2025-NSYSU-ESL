LIB_DIR=-L/usr/local/systemc-2.3.1a/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.1a/include
LIB=-lsystemc
RPATH=-Wl,-rpath=/usr/local/systemc-2.3.1a/lib-linux64

APP=stimgen
BPP=monitor
DPP=Adder
EPP=main


all:
	g++ -o $(EPP) $(EPP).cpp $(APP).cpp $(BPP).cpp $(DPP).cpp $(LIB_DIR) $(INC_DIR) $(LIB) $(RPATH)

clean:
	rm -rf $(EPP) $(EPP).cpp $(APP).cpp $(BPP).cpp $(DPP).cpp $(LIB_DIR) $(INC_DIR) $(LIB) $(RPATH)
