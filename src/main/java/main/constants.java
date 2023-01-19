package main;

public class constants {
    static final  int DEFAULT_NUM_ATOMIC_PER_COMP = 200;
    static final  int DEFAULT_NUM_CONN_PER_ATOMIC = 5;
    static final  int DEFAULT_DOCUMENT_SIZE = 20000;
    static final  int DEFAULT_MANUAL_SIZE = 1000000;
    static final  int DEFAULT_NUM_COMP_PER_MODULE = 1000;
    static final  int DEFAULT_NUM_ASSM_PER_ASSM = 3;
    static final  int DEFAULT_NUM_ASSM_LEVELS = 15;
    static final  int DEFAULT_NUM_COMP_PER_ASSM = 3;
    static final  int DEFAULT_NUM_MODULES = 1;

    static final  int DEFAULT_MIN_MODULE_DATE = 1000;
    static final  int DEFAULT_MAX_MODULE_DATE = 1999;
    static final  int DEFAULT_MIN_ASSM_DATE = 1000;
    static final  int DEFAULT_MAX_ASSM_DATE = 1999;
    static final  int DEFAULT_MIN_ATOMIC_DATE = 1000;
    static final  int DEFAULT_MAX_ATOMIC_DATE = 1999;
    static final  int DEFAULT_MIN_OLD_COMP_DATE = 0;
    static final  int DEFAULT_MAX_OLD_COMP_DATE = 999;
    static final  int DEFAULT_MIN_YOUNG_COMP_DATE = 2000;
    static final  int DEFAULT_MAX_YOUNG_COMP_DATE = 2999;
    static final  int DEFAULT_YOUNG_COMP_FRAC = 10;
    static final  int DEFAULT_TYPE_SIZE = 10;
    static final  int DEFAULT_NUM_TYPES = 10;
    static final  int DEFAULT_XY_RANGE = 100000;
    static final  int DEFAULT_TITLE_SIZE = 40;

    static final  int DEFAULT_TRAVERSAL_RATIO = 5;
    static final  int DEFAULT_SHORT_TRAVERSAL_RATIO = 40;
    static final  int DEFAULT_OPERATIONS_RATIO = 45;
    static final  int DEFAULT_STRUCTURAL_MODIFICATIONS_RATIO = 10;

    // just for testing make it 70%
    static final  int DEFAULT_READ_ONLY_OPERATIONS_RATIO = 70;

    static final  int DEFAULT_THREAD_NUM = 1;
    static final  int DEFAULT_EXPERIMENT_LENGTH_MS = 1000;

    static final  int DEFAULT_MAX_LOW_TTC = 999;
    static final  int DEFAULT_HIGH_TTC_ENTRIES = 200;
    static final  double DEFAULT_HIGH_TTC_LOG_BASE = 1.03;

    static final  boolean DEFAULT_STRUCTURE_MODIFICATION_ENABLED = true;
    static final  boolean DEFAULT_LONG_TRAVERSALS_ENABLED = true;
    static final  boolean DEFAULT_REPORT_TTC_HISTOGRAMS = false;


    static final  double MAX_TO_INITIAL_RATIO = 1.05;

    static final  lockingType DEFAULT_LOCK_TYPE = lockingType.lock_coarse;
    static final  boolean DEFAULT_THREAD_BLOCKING = false;
}
