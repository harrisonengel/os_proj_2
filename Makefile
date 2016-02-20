all: osp2a osp2c

osp2a: osp2a.cpp
	g++ -o osp2a osp2a.cpp -lpthread

osp2c: osp2c.cpp
	g++ -o osp2c osp2c.cpp -lpthread

clean:
	rm *.o osp2a osp2c
