include Makefile.in

.PHONY: clean docs

OBJFILES = $(OBJ_DIR)/sb7_lock.o \
	$(OBJ_DIR)/mersenne.o $(OBJ_DIR)/random.o $(OBJ_DIR)/helpers.o \
	$(OBJ_DIR)/thread.o $(OBJ_DIR)/thread_fun.o $(OBJ_DIR)/parameters.o \
	$(OBJ_DIR)/manual.o $(OBJ_DIR)/design_obj.o $(OBJ_DIR)/assembly.o \
	$(OBJ_DIR)/composite_part.o $(OBJ_DIR)/document.o $(OBJ_DIR)/atomic_part.o \
	$(OBJ_DIR)/data_holder.o $(OBJ_DIR)/id_pool.o $(OBJ_DIR)/benchmark.o \
	$(OBJ_DIR)/operations.o \
	$(OBJ_DIR)/traversal_ops_lc.o $(OBJ_DIR)/query_ops_lc.o $(OBJ_DIR)/operation_ops_lc.o \
	$(OBJ_DIR)/structural_modification_ops_lc.o $(OBJ_DIR)/short_traversal_ops_lc.o \
	$(OBJ_DIR)/lock_srv_lc.o \
	$(OBJ_DIR)/traversal_ops_lm.o $(OBJ_DIR)/query_ops_lm.o $(OBJ_DIR)/operation_ops_lm.o \
	$(OBJ_DIR)/structural_modification_ops_lm.o $(OBJ_DIR)/short_traversal_ops_lm.o \
	$(OBJ_DIR)/lock_srv_lm.o \
	$(OBJ_DIR)/traversal_ops_ca.o $(OBJ_DIR)/query_ops_ca.o $(OBJ_DIR)/operation_ops_ca.o \
	$(OBJ_DIR)/structural_modification_ops_ca.o $(OBJ_DIR)/labelAssignmentTraversal.o\
	$(OBJ_DIR)/lockPool.o $(OBJ_DIR)/lscaHelpers.o\
	$(OBJ_DIR)/labelAssignmentTest.o $(OBJ_DIR)/CArelabelling.o $(OBJ_DIR)/DomRelabelling.o\
	$(OBJ_DIR)/traversal_ops_dom.o $(OBJ_DIR)/query_ops_dom.o $(OBJ_DIR)/operation_ops_dom.o \
    $(OBJ_DIR)/structural_modification_ops_dom.o\


all: $(OBJ_DIR)/sb7_lock

# main
$(OBJ_DIR)/sb7_lock: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) -v
	cp $(OBJ_DIR)/sb7_lock .

$(OBJ_DIR)/sb7_lock.o: $(SRC_DIR)/sb7_lock.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/sb7_lock.cpp -c -o $@




# build struct
$(OBJ_DIR)/design_obj.o: $(SRC_DIR)/struct/design_obj.cpp $(SRC_DIR)/struct/design_obj.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/design_obj.cpp -c -o $@

$(OBJ_DIR)/manual.o: $(SRC_DIR)/struct/manual.cpp $(SRC_DIR)/struct/manual.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/manual.cpp -c -o $@

$(OBJ_DIR)/document.o: $(SRC_DIR)/struct/document.cpp $(SRC_DIR)/struct/document.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/document.cpp -c -o $@

$(OBJ_DIR)/assembly.o: $(SRC_DIR)/struct/assembly.cpp $(SRC_DIR)/struct/assembly.h \
		$(OBJ_DIR)/parameters.o
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/assembly.cpp -c -o $@

$(OBJ_DIR)/composite_part.o: $(SRC_DIR)/struct/composite_part.cpp \
		$(SRC_DIR)/struct/composite_part.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/composite_part.cpp -c -o $@

$(OBJ_DIR)/atomic_part.o: $(SRC_DIR)/struct/atomic_part.cpp $(SRC_DIR)/struct/atomic_part.h \
		$(SRC_DIR)/struct/connection.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/struct/atomic_part.cpp -c -o $@

#
$(OBJ_DIR)/data_holder.o: $(SRC_DIR)/data_holder.cpp $(SRC_DIR)/data_holder.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/data_holder.cpp -c -o $@

$(OBJ_DIR)/thread.o: $(SRC_DIR)/thread/thread.cpp $(SRC_DIR)/thread/thread.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/thread/thread.cpp -c -o $@

$(OBJ_DIR)/thread_fun.o: $(SRC_DIR)/thread/thread_fun.cpp $(SRC_DIR)/thread/thread_fun.h \
		$(SRC_DIR)/thread/thread.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/thread/thread_fun.cpp -c -o $@

$(OBJ_DIR)/id_pool.o: $(SRC_DIR)/id_pool.cpp $(SRC_DIR)/id_pool.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/id_pool.cpp -c -o $@

$(OBJ_DIR)/benchmark.o: $(SRC_DIR)/benchmark.cpp $(SRC_DIR)/benchmark.h \
		$(OBJ_DIR)/thread_fun.o
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/benchmark.cpp -c -o $@

# build random impl
$(OBJ_DIR)/mersenne.o: $(SRC_DIR)/randomc/mersenne.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/randomc/mersenne.cpp -c -o $@

$(OBJ_DIR)/random.o: $(SRC_DIR)/random.cpp $(SRC_DIR)/random.h $(OBJ_DIR)/mersenne.o
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/random.cpp -c -o $@

# settings
$(OBJ_DIR)/parameters.o: $(SRC_DIR)/parameters.cpp $(SRC_DIR)/parameters.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/parameters.cpp -c -o $@

# helpers
$(OBJ_DIR)/helpers.o: $(SRC_DIR)/helpers.cpp $(SRC_DIR)/helpers.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/helpers.cpp -c -o $@

#operations
# base
$(OBJ_DIR)/operations.o: $(SRC_DIR)/operations/operations.cpp $(SRC_DIR)/operations/operations.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/operations.cpp -c -o $@

# lc
$(OBJ_DIR)/traversal_ops_lc.o: $(SRC_DIR)/operations/locking_coarse/traversal_ops_lc.cpp \
		$(SRC_DIR)/operations/locking_coarse/traversal_ops_lc.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/traversal_ops_lc.cpp -c -o $@

$(OBJ_DIR)/query_ops_lc.o: $(SRC_DIR)/operations/locking_coarse/query_ops_lc.cpp \
		$(SRC_DIR)/operations/locking_coarse/query_ops_lc.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/query_ops_lc.cpp -c -o $@

$(OBJ_DIR)/short_traversal_ops_lc.o: $(SRC_DIR)/operations/locking_coarse/short_traversal_ops_lc.cpp \
		$(SRC_DIR)/operations/locking_coarse/short_traversal_ops_lc.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/short_traversal_ops_lc.cpp -c -o $@

$(OBJ_DIR)/operation_ops_lc.o: $(SRC_DIR)/operations/locking_coarse/operation_ops_lc.cpp \
		$(SRC_DIR)/operations/locking_coarse/operation_ops_lc.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/operation_ops_lc.cpp -c -o $@

$(OBJ_DIR)/structural_modification_ops_lc.o: \
		$(SRC_DIR)/operations/locking_coarse/structural_modification_ops_lc.cpp \
		$(SRC_DIR)/operations/locking_coarse/structural_modification_ops_lc.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/structural_modification_ops_lc.cpp -c -o $@

$(OBJ_DIR)/lock_srv_lc.o: $(SRC_DIR)/operations/locking_coarse/lock_srv_lc.h \
		$(SRC_DIR)/operations/locking_coarse/lock_srv_lc.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_coarse/lock_srv_lc.cpp -c -o $@

# lm
$(OBJ_DIR)/traversal_ops_lm.o: $(SRC_DIR)/operations/locking_medium/traversal_ops_lm.cpp \
		$(SRC_DIR)/operations/locking_medium/traversal_ops_lm.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/traversal_ops_lm.cpp -c -o $@

$(OBJ_DIR)/query_ops_lm.o: $(SRC_DIR)/operations/locking_medium/query_ops_lm.cpp \
		$(SRC_DIR)/operations/locking_medium/query_ops_lm.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/query_ops_lm.cpp -c -o $@

$(OBJ_DIR)/short_traversal_ops_lm.o: $(SRC_DIR)/operations/locking_medium/short_traversal_ops_lm.cpp \
		$(SRC_DIR)/operations/locking_medium/short_traversal_ops_lm.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/short_traversal_ops_lm.cpp -c -o $@

$(OBJ_DIR)/operation_ops_lm.o: $(SRC_DIR)/operations/locking_medium/operation_ops_lm.cpp \
		$(SRC_DIR)/operations/locking_medium/operation_ops_lm.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/operation_ops_lm.cpp -c -o $@

$(OBJ_DIR)/structural_modification_ops_lm.o: $(SRC_DIR)/operations/locking_medium/structural_modification_ops_lm.cpp \
		$(SRC_DIR)/operations/locking_medium/structural_modification_ops_lm.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/structural_modification_ops_lm.cpp -c -o $@

$(OBJ_DIR)/lock_srv_lm.o: $(SRC_DIR)/operations/locking_medium/lock_srv_lm.h \
		$(SRC_DIR)/operations/locking_medium/lock_srv_lm.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_medium/lock_srv_lm.cpp -c -o $@


# locking CA

$(OBJ_DIR)/labelAssignmentTraversal.o: $(SRC_DIR)/labelAssignmentTraversal.cpp \
		$(SRC_DIR)/labelAssignmentTraversal.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/labelAssignmentTraversal.cpp -c -o $@

$(OBJ_DIR)/labelAssignmentTest.o: $(SRC_DIR)/labelAssignmentTest.cpp \
		$(SRC_DIR)/labelAssignmentTest.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/labelAssignmentTest.cpp -c -o $@

$(OBJ_DIR)/lockPool.o: $(SRC_DIR)/lockPool.cpp \
		$(SRC_DIR)/lockPool.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/lockPool.cpp -c -o $@

$(OBJ_DIR)/lscaHelpers.o: $(SRC_DIR)/lscaHelpers.cpp \
		$(SRC_DIR)/lscaHelpers.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/lscaHelpers.cpp -c -o $@

$(OBJ_DIR)/CArelabelling.o: $(SRC_DIR)/CArelabelling.cpp \
		$(SRC_DIR)/CArelabelling.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/CArelabelling.cpp -c -o $@


$(OBJ_DIR)/traversal_ops_ca.o: $(SRC_DIR)/operations/locking_ca/traversal_ops_ca.cpp \
		$(SRC_DIR)/operations/locking_ca/traversal_ops_ca.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_ca/traversal_ops_ca.cpp -c -o $@

$(OBJ_DIR)/query_ops_ca.o: $(SRC_DIR)/operations/locking_ca/query_ops_ca.cpp \
		$(SRC_DIR)/operations/locking_ca/query_ops_ca.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_ca/query_ops_ca.cpp -c -o $@

$(OBJ_DIR)/operation_ops_ca.o: $(SRC_DIR)/operations/locking_ca/operation_ops_ca.cpp \
		$(SRC_DIR)/operations/locking_ca/operation_ops_ca.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_ca/operation_ops_ca.cpp -c -o $@

$(OBJ_DIR)/structural_modification_ops_ca.o: $(SRC_DIR)/operations/locking_ca/structural_modification_ops_ca.cpp \
		$(SRC_DIR)/operations/locking_ca/structural_modification_ops_ca.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_ca/structural_modification_ops_ca.cpp -c -o $@




# locking Dom
$(OBJ_DIR)/traversal_ops_dom.o: $(SRC_DIR)/operations/locking_domLock/traversal_ops_dom.cpp \
		$(SRC_DIR)/operations/locking_domLock/traversal_ops_dom.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_domLock/traversal_ops_dom.cpp -c -o $@

$(OBJ_DIR)/query_ops_dom.o: $(SRC_DIR)/operations/locking_domLock/query_ops_dom.cpp \
		$(SRC_DIR)/operations/locking_domLock/query_ops_dom.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_domLock/query_ops_dom.cpp -c -o $@

$(OBJ_DIR)/operation_ops_dom.o: $(SRC_DIR)/operations/locking_domLock/operation_ops_dom.cpp \
		$(SRC_DIR)/operations/locking_domLock/operation_ops_dom.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_domLock/operation_ops_dom.cpp -c -o $@

$(OBJ_DIR)/structural_modification_ops_dom.o: $(SRC_DIR)/operations/locking_domLock/structural_modification_ops_dom.cpp \
		$(SRC_DIR)/operations/locking_domLock/structural_modification_ops_dom.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/operations/locking_domLock/structural_modification_ops_dom.cpp -c -o $@


$(OBJ_DIR)/DomRelabelling.o: $(SRC_DIR)/DomRelabelling.cpp \
		$(SRC_DIR)/DomRelabelling.h
	mkdir -p $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/DomRelabelling.cpp -c -o $@


# general
# TODO make this work even when there are no files to delete
clean:
	rm -r $(TARGET_DIR)
	rm sb7_lock

docs:
	mkdir -p $(TARGET_DOCS_DIR)
	doxygen $(SRC_DOCS_DIR)/Doxyfile

