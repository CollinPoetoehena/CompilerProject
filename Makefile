TEST_DIRS := basic # nested_funs arrays preprocess
TEST_CFLAGS := ""
TEST_RUN_FUNCTIONAL := 1 # set to one when you want to test functional tests
TEST_CIVAS := bin/civas
TEST_CIVVM := bin/civvm
TEST_CIVCC := build-debug/civicc

.PHONY: help debug release dist clean deps coconut

help:
	@echo "Targets:"
	@echo "  debug  : Generate build artifacts for a debug build in build-debug"
	@echo "  release: Generate build artifacts for a release build in build-release"
	@echo "  dist   : Pack civicc and coconut into a tar.gz file. Use this for creating a submission"
	@echo "  clean  : Remove all build directories and created dist files"

coconut:
	make -C coconut

debug: coconut
	@cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B build-$@/

release: coconut
	@cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B build-$@/


dist:
	bash scripts/dist.sh

clean:
	rm -f *.tar*
	rm -rf build*/

check: debug
		@cd test; \
			CIVAS=../$(TEST_CIVAS) \
			CIVVM=../$(TEST_CIVVM) \
			CIVCC=../$(TEST_CIVCC) \
			RUN_FUNCTIONAL=$(TEST_RUN_FUNCTIONAL) \
			bash run.bash $(TEST_DIRS)

