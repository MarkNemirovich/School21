##############################################################
# Спасибо Владиславу @lothostr за этот мейк и подробный гайд #
##############################################################

#  ///////////////////  VARIABLES  ////////////////////
CHECK_INCLUDES=unit_tests/includes.check
CHECK_FILES=$(filter-out $(CHECK_INCLUDES), $(wildcard unit_tests/*.check))

#  ////////////////////  OS CHECK  ////////////////////
unittests_nofork: unittests
ifeq ($(UNAME),Linux)
	sed -i 's/runner_run_all/srunner_set_fork_status(sr, CK_NOFORK);\n\n srunner_run_all/' $^.c
endif
ifeq ($(UNAME),Darwin)
	sed -i '' 's/runner_run_all/srunner_set_fork_status(sr, CK_NOFORK);\n\n srunner_run_all/' $^.c
endif

#  ////////////////////  TARGETS  /////////////////////

_unittests.check: $(CHECK_INCLUDES) $(CHECK_FILES)
	$(MAKE) test_numbering
	cat $^ > unit_tests/$@

unittests: _unittests.check
	checkmk clean_mode=1 unit_tests/$^ > $@.c
	rm -f unit_tests/$^
	clang-format -i -style=Google $@.c

# Вот за это особенно огромное спасибо <3
test_numbering:
	@for file in $$(find unit_tests -name "*.check"); do \
		cp $$file $$file.bak; \
		awk -v count=1 -v prev="" ' \
		/^#test/ { \
			split($$0, a, " "); \
			gsub(/[0-9]+$$/, "", a[2]); \
			if(a[2] != prev){ \
				count = 1; \
				prev = a[2]; \
			} \
			printf "%s %s%d", a[1], a[2], count++; \
			for (i=3; i<=length(a); i++) printf " %s", a[i]; \
			print ""; \
		} \
		!/^#test/ {print $$0}' $$file.bak > $$file; \
		rm $$file.bak; \
	done

#  /////////////////////  EXTRAS  //////////////////////
.PHONY: _unittests.check unittests nofork test_numbering