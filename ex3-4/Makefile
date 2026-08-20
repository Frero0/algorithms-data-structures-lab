JAVAC ?= javac
JAVA ?= java

SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
JUNIT_JAR := $(LIB_DIR)/junit-4.13.2.jar
HAMCREST_JAR := $(LIB_DIR)/hamcrest-core-1.3.jar
TEST_CLASSPATH := $(BUILD_DIR):$(JUNIT_JAR):$(HAMCREST_JAR)
GRAPH ?= examples/sample-graph.csv

MAIN_SOURCES := $(shell find "$(SRC_DIR)" -name '*.java' \
	! -name '*Tests.java' \
	! -name '*_test.java' \
	! -name '*Runner.java' \
	! -name '*_run.java')
TEST_SOURCES := \
	$(SRC_DIR)/priorityqueue/PriorityQueueTests.java \
	$(SRC_DIR)/graph/GraphTests.java \
	$(SRC_DIR)/prim/PrimTests.java

define run_junit
	@run_dir=$$(mktemp -d "/tmp/algorithms-java.XXXXXX"); \
	status=0; \
	cp -R "$(BUILD_DIR)" "$$run_dir/build" || status=$$?; \
	cp "$(JUNIT_JAR)" "$(HAMCREST_JAR)" "$$run_dir/" || status=$$?; \
	if [ $$status -eq 0 ]; then \
		$(JAVA) -cp "$$run_dir/build:$$run_dir/junit-4.13.2.jar:$$run_dir/hamcrest-core-1.3.jar" \
			org.junit.runner.JUnitCore $(1) || status=$$?; \
	fi; \
	rm -rf "$$run_dir"; \
	exit $$status
endef

.PHONY: all compile demo run-prim test-compile test test-priorityqueue test-graph test-prim clean

all: compile test-compile

compile:
	mkdir -p $(BUILD_DIR)
	$(JAVAC) -Xlint:all,-serial -d $(BUILD_DIR) $(MAIN_SOURCES)

test-compile: compile
	$(JAVAC) -Xlint:all,-serial -cp "$(TEST_CLASSPATH)" -d $(BUILD_DIR) $(TEST_SOURCES)

test-priorityqueue: test-compile
	$(call run_junit,priorityqueue.PriorityQueueTests)

test-graph: test-compile
	$(call run_junit,graph.GraphTests)

test-prim: test-compile
	$(call run_junit,prim.PrimTests)

test: test-priorityqueue test-graph test-prim

run-prim: compile
	@run_dir=$$(mktemp -d "/tmp/algorithms-prim.XXXXXX"); \
	status=0; \
	cp -R "$(BUILD_DIR)" "$$run_dir/build" || status=$$?; \
	cp "$(GRAPH)" "$$run_dir/graph.csv" || status=$$?; \
	if [ $$status -eq 0 ]; then \
		$(JAVA) -cp "$$run_dir/build" prim.Prim "$$run_dir/graph.csv" || status=$$?; \
	fi; \
	rm -rf "$$run_dir"; \
	exit $$status

demo: run-prim

clean:
	rm -rf $(BUILD_DIR)
