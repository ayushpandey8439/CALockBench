package main.operations.coarse;

import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class lockserver {
    private static ReentrantReadWriteLock mutex = new ReentrantReadWriteLock();

    public static void readLock(){
        mutex.readLock().lock();
    }
    public static void readUnlock(){
        mutex.readLock().unlock();
    }

    public static void writeLock(){
        mutex.writeLock().lock();
    }
    public static void writeUnlock(){
        mutex.writeLock().unlock();
    }
}
