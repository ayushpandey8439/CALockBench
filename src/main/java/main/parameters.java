package main;

import org.apache.commons.cli.*;


public class parameters {
   static int numAtomicPerComp;
    static int numConnPerAtomic;
    private static int documentSize;
    private static int manualSize;
    private static int numCompPerModule;
    static int numAssmPerAssm;
    static int numAssmLevels;
    static int numCompPerAssm;
    private static int numModules;

    static int initialTotalCompParts;
    static int initialTotalBaseAssemblies;
    static int initialTotalComplexAssemblies;

    private static int maxCompParts;
    private static int maxAtomicParts;
    private static int maxBaseAssemblies;
    private static int maxComplexAssemblies;

    static int minModuleDate;
    static int maxModuleDate;
    static int minAssmDate;
    static int maxAssmDate;
    public static int minAtomicDate;
    public static int maxAtomicDate;
    static int minOldCompDate;
    static int maxOldCompDate;
    static int minYoungCompDate;
    static int maxYoungCompDate;
    static int youngCompFrac;
    private static int typeSize;
    private static int numTypes;
    static int xyRange;
    private static int titleSize;

    private static int traversalRatio;
    private static int shortTraversalRatio;
    public static int operationsRatio;
    public static int structuralModificationsRatio;

    public static int readOnlyOperationsRatio;

    public static int threadNum;
    public static int experimentLengthMs;

    //Parameters of the output TTC histograms.
    private static int maxLowTtc;
    private static int highTtcEntries;
    private static double highTtcLogBase;

    private boolean structureModificationEnabled;
    private boolean reportTtcHistograms;

    final double MAX_TO_INITIAL_RATIO = 1.05;

    public static lockingType lockType;

    parameters(){
//        this.numAtomicPerComp=20;
//        this.numConnPerAtomic=6;
//        this.documentSize=20000;
//        this.manualSize=1000000;
//        this.numCompPerModule=50;
//        this.numAssmPerAssm=3;
//        this.numAssmLevels=7;
//        this.numCompPerAssm=3;
//        this.numModules=1;
//
//
//        this.minModuleDate=1000;
//        this.maxModuleDate=1999;
//        this.minAssmDate=1000;
//        this.maxAssmDate=1999;
//        this.minAtomicDate=1000;
//        this.maxAtomicDate=1999;
//        this.minOldCompDate=0;
//        this.maxOldCompDate=999;
//        this.minYoungCompDate=2000;
//        this.maxYoungCompDate=2999;
//        this.youngCompFrac=10;
//        this.typeSize=10;
//        this.numTypes=10;
//        this.xyRange=100000;
//        this.titleSize=40;
//
//        this.traversalRatio=5;
//        this.shortTraversalRatio=40;
//        this.operationsRatio=45;
//        this.structuralModificationsRatio=10;
//
//        this.readOnlyOperationsRatio=70;
//
//        this.threadNum=1;
//        this.experimentLengthMs=1000;
//
//        //Parameters of the output TTC histograms.
//        this.maxLowTtc=999;
//        this.highTtcEntries=200;
//        this.highTtcLogBase=1.03;
//
//        this.structureModificationEnabled=true;
//        this.reportTtcHistograms=false;
//
//
//        this.lockType= main.lockingType.lock_coarse;
//        boolean threadBlocking;
        initDefault();
    }

    public void readParams(String[] args){
        Options options = new Options();
        options.addOption("p", true, "Read only percentage");
        options.addOption("w", true, "Workload Type (r, rw, w)");
        options.addOption("t", true, "Traversals");
        options.addOption("m", true, "Structural modifications");
        options.addOption("n", true, "Number of threads");
        options.addOption("d", true, "Experiment duration");
        options.addOption("s", true, "Hierarchy Size");
        options.addOption("l", true, "Lock Type");

        CommandLineParser parser = new DefaultParser();
        try{
            CommandLine cmd = parser.parse(options, args);
            if(cmd.hasOption("p")){
                if(cmd.hasOption('w')){
                    System.out.println("Both read only percent and workload type set. Ignoring readonly percentage");
                }else {
                    int percent = Integer.parseInt(cmd.getOptionValue("p"));
                    if(percent>0 && percent<100){
                        readOnlyOperationsRatio = percent;
                    } else {
                        System.out.println("Readonly percentage parameter has invalid value. Ignoring");
                    }
                }
            }

            if(cmd.hasOption('w')){
                String type = cmd.getOptionValue('w');
                switch (type){
                    case "r":
                        readOnlyOperationsRatio = 90;
                        break;
                    case "rw":
                        readOnlyOperationsRatio = 60;
                        break;
                    case "w":
                        readOnlyOperationsRatio = 10;
                        break;
                    default:
                        System.out.println("Workload type parameter has invalid value. Ignoring");
                }
            }

            if(cmd.hasOption('m')){
                structureModificationEnabled = Boolean.parseBoolean(cmd.getOptionValue('m'));
            }
            if(cmd.hasOption('n')){
                int threads = Integer.parseInt(cmd.getOptionValue("n"));
                if(threads>=1){
                    threadNum = threads;
                } else {
                    System.out.println("Thread count parameter has invalid value. Ignoring");
                }
            }
            if(cmd.hasOption('d')) {
                int duration = Integer.parseInt(cmd.getOptionValue("d"));
                if (duration > 0) {
                    experimentLengthMs = duration;
                } else {
                    System.out.println("Experiment duration parameter has invalid value. Ignoring");
                }
            }
            if(cmd.hasOption('s')){
                String size = cmd.getOptionValue('s');
                switch (size){
                    case "s":
                        numAtomicPerComp = 20;
                        numCompPerModule = 50;
                        break;
                    case "m":
                        numAtomicPerComp = 20;
                        numCompPerModule = 500;
                        break;
                    case "b":
                        numAtomicPerComp = 200;
                        numCompPerModule = 500;
                        break;
                    default:
                        System.out.println("Size parameter has invalid value. Ignoring");
                }
            }

            if(cmd.hasOption('l')){
                String l = cmd.getOptionValue('l');
                switch (l){
                    case "c":
                        lockType = lockingType.lock_coarse;
                        break;
                    case "m":
                        lockType = lockingType.lock_medium;
                        break;
                    case "ca":
                        lockType = lockingType.lock_ca;
                        break;
                    case "dom":
                        lockType = lockingType.lock_dom;
                        break;
                    default:
                        System.out.println("Lock type parameter has invalid value. Ignoring");
                }
            }

        } catch (UnrecognizedOptionException e){
            System.err.println("Unrecognised option supplied in the flags. Params set to defaults. ");
        }catch (Exception e ){
            e.printStackTrace();
        }
    }


    public void print(){
        System.out.println("Configuration Parameters:");
        System.out.println("Atomic parts per component: "+ numAtomicPerComp);
        System.out.println("Components per module: "+numCompPerModule);
        System.out.println("Operations ratio: "+ operationsRatio);
        System.out.println("Readonly main.operations ratio: "+ readOnlyOperationsRatio);
        System.out.println("Structural modifications ratio: "+ structuralModificationsRatio);
        System.out.println("Number of threads: "+ threadNum);
        System.out.println("Experiment length: "+ experimentLengthMs);
        System.out.println("Lock type: "+ lockType);
    }

    void setNumAtomicPerComp(int val) {
        numAtomicPerComp = val;
        calcMaxAtomicParts();
    }
    void calcMaxAtomicParts() {
        maxAtomicParts =
                maxCompParts * numAtomicPerComp;
    }

    void setNumConnPerAtomic(int val) {
        numConnPerAtomic = val;
    }

    void setNumCompPerModule(int val) {
        numCompPerModule = val;
        calcInitialTotalCompParts();
    }

    void setNumAssmPerAssm(int val) {
        numAssmPerAssm = val;
        calcInitialTotalBaseAssemblies();
    }

    void setNumAssmLevels(int val) {
        numAssmLevels = val;
        calcInitialTotalBaseAssemblies();
    }

    void setNumCompPerAssm(int val) {
        numCompPerAssm = val;
        calcInitialTotalCompParts();
    }

    void setNumModules(int val) {
        numModules = val;
        calcInitialTotalCompParts();
    }

    void calcInitialTotalCompParts() {
        initialTotalCompParts =
                numModules * numCompPerModule;
        calcMaxCompParts();
    }

    void calcInitialTotalBaseAssemblies() {
        initialTotalBaseAssemblies =
                (int) Math.pow(numAssmPerAssm, numAssmLevels-1);
        calcInitialTotalComplexAssemblies();
        calcMaxBaseAssemblies();
    }

    void calcInitialTotalComplexAssemblies() {
        initialTotalComplexAssemblies =
                (1 - initialTotalBaseAssemblies) /
                        (1 - numAssmPerAssm);
        calcMaxComplexAssemblies();
    }

    void calcMaxCompParts() {
        maxCompParts =
                (int) (initialTotalCompParts * MAX_TO_INITIAL_RATIO);
        calcMaxAtomicParts();
    }


    void calcMaxBaseAssemblies() {
        maxBaseAssemblies =
                (int) (initialTotalBaseAssemblies *
                        MAX_TO_INITIAL_RATIO);
    }

    void calcMaxComplexAssemblies() {
        maxComplexAssemblies =
                (int) (initialTotalComplexAssemblies *
                        MAX_TO_INITIAL_RATIO);
    }

    void setMinModuleDate(int val) {
        minModuleDate = val;
    }

    void setMaxModuleDate(int val) {
        maxModuleDate = val;
    }

    void setMinAssmDate(int val) {
        minAssmDate = val;
    }

    void setMaxAssmDate(int val) {
        maxAssmDate = val;
    }

    void setMinAtomicDate(int val) {
        minAtomicDate = val;
    }

    void setMaxAtomicDate(int val) {
        maxAtomicDate = val;
    }

    void setMinOldCompDate(int val) {
        minOldCompDate = val;
    }

    void setMaxOldCompDate(int val) {
        maxOldCompDate = val;
    }

    void setMinYoungCompDate(int val) {
        minYoungCompDate = val;
    }

    void setMaxYoungCompDate(int val) {
        maxYoungCompDate = val;
    }

    void setYoungCompFrac(int val) {
        youngCompFrac = val;
    }

    void setTypeSize(int val) {
        typeSize = val;
    }

    void setNumTypes(int val) {
        numTypes = val;
    }

    void setXYRange(int val) {
        xyRange = val;
    }

    void setTitleSize(int val) {
        titleSize = val;
    }

    void setTraversalsRatio(int val) {
        traversalRatio = val;
    }

    void setShortTraversalsRatio(int val) {
        shortTraversalRatio = val;
    }

    void setOperationsRatio(int val) {
        operationsRatio = val;
    }

    void setStructuralModificationsRatio(int val) {
        structuralModificationsRatio = val;
    }

    void setReadOnlyOperationsRatio(int val) {
        readOnlyOperationsRatio = val;
    }

    void setThreadNum(int val) {
        threadNum = val;
    }

    void setExperimentLengthMs(int val) {
        experimentLengthMs = val;
    }

    void setMaxLowTtc(int val) {
        maxLowTtc = val;
    }

    void setHighTtcEntries(int val) {
        highTtcEntries = val;
    }

    void setHighTtcLogBase(double val) {
        highTtcLogBase = val;
    }

    void setStructureModificationEnabled(boolean val) {
        structureModificationEnabled = val;
    }

    void setReportTtcHistograms(boolean val) {
        reportTtcHistograms = val;
    }



    void setLockType(lockingType lt) {
        lockType = lt;
    }


    void initDefault(){
        setNumAtomicPerComp(constants.DEFAULT_NUM_ATOMIC_PER_COMP);
        setNumConnPerAtomic(constants.DEFAULT_NUM_CONN_PER_ATOMIC);
        setNumCompPerModule(constants.DEFAULT_NUM_COMP_PER_MODULE);
        setNumAssmPerAssm(constants.DEFAULT_NUM_ASSM_PER_ASSM);
        setNumAssmLevels(constants.DEFAULT_NUM_ASSM_LEVELS);
        setNumCompPerAssm(constants.DEFAULT_NUM_COMP_PER_ASSM);
        setNumModules(constants.DEFAULT_NUM_MODULES);

        setMinModuleDate(constants.DEFAULT_MIN_MODULE_DATE);
        setMaxModuleDate(constants.DEFAULT_MAX_MODULE_DATE);
        setMinAssmDate(constants.DEFAULT_MIN_ASSM_DATE);
        setMaxAssmDate(constants.DEFAULT_MAX_ASSM_DATE);
        setMinAtomicDate(constants.DEFAULT_MIN_ATOMIC_DATE);
        setMaxAtomicDate(constants.DEFAULT_MAX_ATOMIC_DATE);
        setMinOldCompDate(constants.DEFAULT_MIN_OLD_COMP_DATE);
        setMaxOldCompDate(constants.DEFAULT_MAX_OLD_COMP_DATE);
        setMinYoungCompDate(constants.DEFAULT_MIN_YOUNG_COMP_DATE);
        setMaxYoungCompDate(constants.DEFAULT_MAX_YOUNG_COMP_DATE);
        setYoungCompFrac(constants.DEFAULT_YOUNG_COMP_FRAC);
        setTypeSize(constants.DEFAULT_TYPE_SIZE);
        setNumTypes(constants.DEFAULT_NUM_TYPES);
        setXYRange(constants.DEFAULT_XY_RANGE);
        setTitleSize(constants.DEFAULT_TITLE_SIZE);

        setTraversalsRatio(constants.DEFAULT_TRAVERSAL_RATIO);
        setShortTraversalsRatio(constants.DEFAULT_SHORT_TRAVERSAL_RATIO);
        setOperationsRatio(constants.DEFAULT_OPERATIONS_RATIO);
        setStructuralModificationsRatio(constants.DEFAULT_STRUCTURAL_MODIFICATIONS_RATIO);

        setReadOnlyOperationsRatio(constants.DEFAULT_READ_ONLY_OPERATIONS_RATIO);

        setThreadNum(constants.DEFAULT_THREAD_NUM);
        setExperimentLengthMs(constants.DEFAULT_EXPERIMENT_LENGTH_MS);

        setMaxLowTtc(constants.DEFAULT_MAX_LOW_TTC);
        setHighTtcEntries(constants.DEFAULT_HIGH_TTC_ENTRIES);
        setHighTtcLogBase(constants.DEFAULT_HIGH_TTC_LOG_BASE);

        setStructureModificationEnabled(constants.DEFAULT_STRUCTURE_MODIFICATION_ENABLED);
        setReportTtcHistograms(constants.DEFAULT_REPORT_TTC_HISTOGRAMS);


        setLockType(constants.DEFAULT_LOCK_TYPE);
    }

}