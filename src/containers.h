//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_CONTAINERS_H
#define STMBENCH_CONTAINERS_H


#include <set>
#include <map>

using namespace std;

namespace sb7 {

    /**
     * <p>
     * Iterator class represents Java-like iterators for traversals through
     * all used containers. Public interface doesn't depend on underlying
     * class used, but only on type of objects stored in the container.
     * </p>
     *
     * TODO it is probably good idea to transform this into more c++ like
     * iterator classes
     *
     */
    template<typename T>
    class Iterator {
    public:
        /**
         * Checks if there are more elements in the container.
         *
         * @return true if there are more elements in the container
         * false otherwise
         */
        virtual bool has_next() const = 0;

        /**
         * Accesses elements in the container. After returning next
         * element it advances iterator to the next element.
         *
         * @return next element in the collection, according to the
         * underlying collection ordering
         */
        virtual T next() = 0;

        /**
         * Destructor that can be overloaded by all implementing classes.
         */
        virtual ~Iterator() = default;
    };

    // forward declaration of set iterator
    template<typename T>
    class SetIterator;

    /**
     * <p>
     * Set container used in sb7. It encapsulates standard STL set. Underlying
     * container implementation can easily be changed if needed.
     * </p>
     */
    template<class T>
    class Set {
    protected:
        typedef set<T> inner_set;
        typedef typename inner_set::const_iterator inner_const_iterator;
        typedef typename inner_set::iterator inner_iterator;
    public:
        /**
         * Default container constructor.
         */
        Set() = default;

        /**
         * Set destructor.
         */
        virtual ~Set() = default;

        /**
         * Add new element to the container. If element already exists
         * it is not added and false is returned.
         *
         * @param[in] el element to add to the set
         *
         * @return true if element was added, false otherwise
         */
        bool add(const T &el) {
            pair<inner_const_iterator, bool> p = inner.insert(el);
            return p.second;
        }

        /**
         * Remove element from the container.
         *
         * @param[in] el element to remove from set
         *
         * @return true if element was removed, false otherwise
         */
        bool remove(T &el) {
            inner_const_iterator iter = inner.find(el);
            bool ret;

            if (iter == inner.end()) {
                ret = false;
            } else {
                inner.erase(iter);
                ret = true;
            }

            return ret;
        }

        /**
         * Function returns iterator for accessing elements of the
         * container.
         *
         * @return iterator pointing at the beginning of the container
         */
        SetIterator<T> getIter() const {
            return SetIterator<T>(this->inner);
        }

        int size() const {
            return inner.size();
        }

        /**
         * Check if set contains element t.
         */
        bool contains(const T &el) const {
            inner_const_iterator iter = inner.find(el);
            return iter != inner.end();
        }

    private:
        inner_set inner;
    };

    /**
     * Iterator implementation that iterates over set.
     */
    template<typename T>
    class SetIterator : public Iterator<T> {
    private:
        typedef set<T> inner_set;
        typedef typename inner_set::iterator inner_iterator;

    protected:
        inner_iterator curr;
        inner_iterator end;

    public:
        /**
         * Constructor that initializes state so the object can be used
         * to iterate over set.
         *
         * @param[in] set Set to iterate over.
         *
         */
        explicit SetIterator(const inner_set &set) {
            curr = set.begin();
            end = set.end();
        }

        /**
         * Destructor for set iterator.
         */
        virtual ~SetIterator() = default;

    public:
        /**
         * @see Iterator<t>.has_next()
         */
        virtual bool has_next() const {
            return !(curr == end);
        }

        /**
         * @see Iterator<t>.next()
         */
        virtual T next() {
            T ret = *curr;
            curr++;
            return ret;
        }
    };

    // forward bag iterator declaration
    template<typename T>
    class BagIterator;

    /**
     * <p>
     * Bag container used in sb7. It encapsulates standard STL multiset.
     * Underlying container implementation can easily be changed if needed.
     * </p>
     */
    template<class T>
    class Bag {
    protected:
        typedef multiset<T> inner_multiset;
        typedef typename inner_multiset::const_iterator
                inner_const_iterator;
        typedef typename inner_multiset::iterator inner_iterator;

    public:
        /**
         * Default container constructor.
         */
        Bag() = default;

        /**
         * Bag destructor.
         */
        virtual ~Bag() = default;

        /**
         * Add new element to the container.
         *
         * @param[in] el element to add to the bag
         *
         * @return true if element was added, false otherwise
         */
        bool add(const T &el) {
            inner.insert(el);
            return true;
        }

        /**
         * Remove element from the container.
         *
         * @param[in] el element to remove from bag
         *
         * @return true if element was removed, false otherwise
         */
        bool remove(T &el) {
            inner_iterator iter = inner.find(el);
            bool ret;

            if (iter == inner.end()) {
                ret = false;
            } else {
                inner.erase(iter);
                ret = true;
            }

            return ret;
        }

        bool removeAll(T &el){
            inner.erase(el);
            return true;
        }

        /**
         * Function returns iterator for accessing elements of the
         * container.
         *
         * @return iterator pointing at the beginning of the container
         */
        BagIterator<T> getIter() const {
            return BagIterator<T>(this->inner);
        }

        int size() const {
            return inner.size();
        }

    private:
        inner_multiset inner;
    };

    /**
     * Iterator implementation that iterates over bag.
     */
    template<typename T>
    class BagIterator : public Iterator<T> {
    protected:
        typedef multiset<T> inner_multiset;
        typedef typename inner_multiset::const_iterator
                inner_const_iterator;
        typedef typename inner_multiset::iterator inner_iterator;

    private:
        inner_iterator curr;
        inner_iterator end;

    public:
        /**
         * Constructor that initializes state so the object can be used
         * to iterate over multiset.
         *
         * @param[in] ms Multiset to iterate over.
         *
         */
        explicit BagIterator(const inner_multiset &ms) {
            curr = ms.begin();
            end = ms.end();
        }

        /**
         * Destructor for bag iterator.
         */
        virtual ~BagIterator() = default;

    public:
        /**
         * @see Iterator<T>.has_next()
         */
        virtual bool has_next() const {
            return !(curr == end);
        }

        /**
         * @see Iterator<T>.next()
         */
        virtual T next() {
            T ret = *curr;
            curr++;
            return ret;
        }
    };

    // forward declaration of map iterator
    template<typename Key, typename Val>
    class MapIterator;

    /**
     * <p>
     * Map container is not directly used in sb7, but it is useful for
     * creating indexes that are used. Class provides general interface
     * for accessing maps. Implementation is based on wrapped STL map.
     * </p>
     */
    template<typename Key, typename Val>
    class Map {
    protected:
        /**
         * Shortcut typedef for using underlying iterators.
         */
        typedef map<Key, Val> inner_map;
        typedef typename inner_map::const_iterator inner_const_iterator;
        typedef typename inner_map::iterator inner_iterator;

    public:
        /**
         * Type used for searching element in the map.
         */
        typedef struct {
            Key key;
            Val val;
            bool found;
        } Query;

        /**
         * Default container constructor.
         */
        Map() = default;

        /**
         * Map destructor.
         */
        virtual ~Map() = default;

        /**
         * Lookup object in the map. Query object is passed as input/output
         * object that describes query and is used for returning value
         * from it. This approach is taken as client code doesn't have
         * access to underlying STL map.
         *
         * @param[in/out] query to perform
         * @return value from the map
         */
        void get(Query &query) const {
            inner_const_iterator iter = inner.find(query.key);
            bool ret = (iter != inner.end());

            if (ret) {
                if(iter->second!= nullptr)
                    query.val = (*iter).second;
                else ret= false;
            }

            query.found = ret;
        }

        /**
         * Add new key/value pair to the map.
         *
         * @param[in] key of new entry
         * @param[in] val of new entry
         */
        void put(const Key &key, const Val &val) {
            inner[key] = val;
        }

        /**
         * Add new key/value pair to the map if it is not in the map
         * already.
         *
         * @param[in] key of new entry
         * @param[in] val of new entry
         */
        void putIfAbsent(const Key &key, const Val &val) {
            inner_iterator iter = inner.find(key);

            if (iter != inner.end()) {
                put(key, val);
            }
        }

        /**
         * Remove element with specified key from the map.
         *
         * @param[in] key of map entry to remove
         *
         * @return true if element was removed, false otherwise
         */
        bool remove(const Key &key) {
            //inner.erase(key);
            inner_iterator iter = inner.find(key);
            bool ret;

            if (iter != inner.end()) {
                //inner.erase(iter);
                iter->second = nullptr;
                ret = true;
            } else {
                ret = false;
            }
            return ret;
        }

        /**
         * Access range of elements from the index.
         *
         * @param[in] l is low key value
         * @param[in] h is high key value
         *
         * @return iterator that can be used to iterate over specified
         * range of values
         */
        MapIterator<Key, Val> getRange(const Key &l, const Key &h) const {
            inner_const_iterator li = inner.lower_bound(l);
            inner_const_iterator hi = inner.upper_bound(h);
            return MapIterator<Key, Val>(li, hi);
        }

        MapIterator<Key, Val> getAll() const {
            inner_const_iterator si = inner.begin();
            inner_const_iterator ei = inner.end();
            return MapIterator<Key, Val>(si, ei);
        }

    private:
        inner_map inner;

    };

    template<typename Key, typename Val>
    class MapIterator : public Iterator<Val> {
    private:
        typedef map<Key, Val> inner_map;
        typedef typename inner_map::const_iterator inner_const_iterator;
        typedef typename inner_map::iterator inner_iterator;

    protected:
        inner_const_iterator curr;
        inner_const_iterator end;

    public:
        /**
         * Construct map iterator from starting and ending value of
         * the iterator.
         *
         * @param [in] s is start iterator
         * @param [in] e is end iterator
         */
        MapIterator(inner_const_iterator &s, inner_const_iterator &e) {
            curr = s;
            end = e;
        }

        /**
         * MapIterator destructor.
         */
        virtual ~MapIterator() = default;

    public:
        /**
         * @see Iterator<T>.has_next()
         */
        virtual bool has_next() const {
            return curr != end;
        }

        /**
         * @see Iterator<T>.next()
         */
        virtual Val next() {
            Val ret = (*curr).second;
            curr++;
            return ret;
        }
    };
}


#endif //STMBENCH_CONTAINERS_H
