TEST_DIR = test

all:
	cd $(TEST_DIR) && $(MAKE) all

clean:
	cd $(TEST_DIR) && $(MAKE) clean

check:
	cd $(TEST_DIR) && $(MAKE) check
