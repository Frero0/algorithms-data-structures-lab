JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	../priorityqueue/PriorityQueueException.java \
	../priorityqueue/AbstractQueue.java \
	../priorityqueue/PriorityQueue.java \
	../Graph/AbstractGraph.java \
	../Graph/AbstractEdge.java \
	../Graph/Arch.java \
	../Graph/Graph.java \
	Prim.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) ../../bld/*/*.class

all: 
	mkdir -p ../../bld && $(JC) -d ../../bld/ $(CLASSES)