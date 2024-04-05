/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <string>
// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include <cassert>

namespace sjtu {

    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    >
    class map {
    public:
        /**
         * the internal type of data.
         * it should have a default constructor, a copy constructor.
         * You can use sjtu::map as value_type by typedef.
         */
        typedef pair<Key, T> value_type;

    private:
        enum subTree {
            left, right
        };

        struct node {
            node *father = nullptr;
            node *left = nullptr;
            node *right = nullptr;
//            Key key;
//            T value;
            value_type val;
            int height = 0;

            node(Key k, T v, node *f = NULL, node *l = NULL, node *r = NULL) : father(f), left(l), right(r),
                                                                               val(value_type(k, v)) {}

            node(value_type valueType, node *f = NULL, node *l = NULL, node *r = NULL) : father(f), left(l), right(r),
                                                                                         val(valueType) {}

            Key &get_key() {
                return val.first;
            }

            T &get_t() {
                return val.second;
            }

//            const Key &_get_key() const {
//                return val.first;
//            }
//
//            const T &_get_t() const {
//                return val.second;
//            }

            node *find(const Key &_key) {
                if (_key == this->get_key()) return this;
                if (Compare()(_key, this->get_key())) {
                    if (left == nullptr) return nullptr;
                    return left->find(_key);
                } else {
                    if (right == nullptr) return nullptr;
                    return right->find(_key);
                }
            }
        };

//        int height(node *);
        int height(node *nd) {
            if (nd == nullptr)return -1;
            return nd->height;
        }

        void back_height(node *nd) {
            if (nd == nullptr)return;
            if (nd->father == nullptr)return;
            nd->father->height = max_height(nd->father->left, nd->father->right) + 1;
            back_height(nd->father);
        }

        size_t max_height(node *l, node *r) {
            if (l == nullptr && r == nullptr) return -1;
            if (l == nullptr) return r->height;
            if (r == nullptr) return l->height;
            return l->height > r->height ? l->height : r->height;
        }

        bool good(node *nd) {
            if (nd == nullptr)return true;
            return (height(nd->left) - height(nd->right) < 2 && height(nd->right) - height(nd->left) < 2 &&
                    nd->height == max_height(nd->left, nd->right) + 1);
        }

//        node *father= nullptr;
        node *root = nullptr;
        size_t _size = 0;

        void clear(node *&nd) {
            if (nd == nullptr) return;
            clear(nd->left);
            clear(nd->right);
            delete nd;
            nd = nullptr;
        }

        void copy(node *&nd, const node *other) {
            if (other == nullptr)return;
            copy(nd->left, other->left);
            copy(nd->right, other->right);
            nd = new node(*other);
        }

        size_t ll(node *&nd) {
            node *f = nd->father, *s = nd, *ls = nd->left, *lsrs = ls->right;
            nd = ls;
            nd->father = f;
            nd->right = s;
            s->father = nd;
            s->left = lsrs;
            if (lsrs != nullptr)lsrs->father = s;
            s->height = max_height(s->left, s->right) + 1;
            nd->height = max_height(nd->left, nd->right) + 1;
            assert(good(nd));
            assert(good(nd->left));
            assert(good(nd->right));
            return nd->height;
        }

        size_t rr(node *&nd) {
            node *f = nd->father, *s = nd, *rs = nd->right, *rsrl = rs->left;
            nd = rs;
            nd->father = f;
            nd->left = s;
            s->father = nd;
            s->right = rsrl;
            if (rsrl != nullptr)rsrl->father = s;
            s->height = max_height(s->left, s->right) + 1;
            nd->height = max_height(nd->left, nd->right) + 1;
            assert(good(nd));
            assert(good(nd->left));
            assert(good(nd->right));
            return nd->height;
        }

        size_t lr(node *&nd) {
            rr(nd->left);
            ll(nd);
            assert(good(nd));
            assert(good(nd->left));
            assert(good(nd->right));
            return nd->height;
        }

        size_t rl(node *&nd) {
            ll(nd->right);
            rr(nd);
            assert(good(nd));
            assert(good(nd->left));
            assert(good(nd->right));
            return nd->height;
        }

        node *_insert(node *&nd, node *f, const Key &key, const T &t, subTree sub = left) {
            if (nd == nullptr) {
                nd = new node(key, t, f, nullptr, nullptr);
                if (f != nullptr) {
                    if (sub == left)f->left = nd;
                    else f->right = nd;
                }
                if (nd->father != nullptr) nd->father->height = max_height(nd->father->left, nd->father->right) + 1;
                back_height(nd);
                return nd;
            }
            node *tmp = nullptr;
            if (Compare()(key, nd->get_key())) {
                tmp = _insert(nd->left, nd, key, t, left);

                if (height(nd->left) - height(nd->right) >= 2) {
                    assert(height(nd->left) - height(nd->right) == 2);
                    if (height(nd->left->left) >= height(nd->left->right))ll(nd);
                    else lr(nd);
                    back_height(nd);
                }
            } else {
                tmp = _insert(nd->right, nd, key, t, right);
                if (height(nd->right) - height(nd->left) >= 2) {
                    assert(height(nd->right) - height(nd->left) == 2);
                    if (height(nd->right->right) >= height(nd->right->left))rr(nd);
                    else rl(nd);
                    back_height(nd);
                }
            }
            assert(good(nd));
            return tmp;
        }

        void remove(node *&nd, node *_rt) {
            assert(nd != nullptr);
            if (nd->left == nullptr && nd->right == nullptr) {
                nd->height = 0;
                if (nd->father->left == nd) {
                    nd->father->height = max_height(nd, nd->father->right);
                    nd->father->left = nullptr;
                    adjust(nd->father, left);
                    delete nd;
                    nd = nullptr;
                } else {
                    nd->father->height = max_height(nd, nd->father->left);
                    nd->father->right = nullptr;
                    adjust(nd->father, right);
                    delete nd;
                    nd = nullptr;
                }

            } else if (nd->right == nullptr) {
                if (nd->father->left == nd) {
                    nd->father->left == nd->left;
                    nd->left->father == nd->father;
                    nd->father->height == max_height(nd->father->left, nd->father->right);
                    adjust(nd->father, left);
                    delete nd;
                    nd = nullptr;
                } else {
                    nd->father->right == nd->left;
                    nd->left->father == nd->father;
                    nd->father->height == max_height(nd->father->left, nd->father->right);
                    adjust(nd->father, right);
                    delete nd;
                    nd = nullptr;
                }
            } else if (nd->left == nullptr) {
                if (nd->father->left == nd) {
                    nd->father->left == nd->right;
                    nd->right->father == nd->father;
                    nd->father->height == max_height(nd->father->left, nd->father->right);
                    adjust(nd->father, left);
                    delete nd;
                    nd = nullptr;
                } else {
                    nd->father->right == nd->right;
                    nd->right->father == nd->father;
                    nd->father->height == max_height(nd->father->left, nd->father->right);
                    adjust(nd->father, right);
                    delete nd;
                    nd = nullptr;
                }
            } else {
                node *tmp = getll(nd->right);
                nd->val = tmp->val;
                remove(tmp, _rt);
            }
        }

        void adjust(node *&t, subTree sub) {
            if (sub == left) {
                assert(height(t->right) - height(t->left) == 1 || height(t->right) - height(t->left) == 0 ||
                       (height(t->right) - height(t->left) == 2 &&
                        (height(t->right->left) - height(t->right->right) == 1 ||
                         height(t->right->left) - height(t->right->right) == 0 ||
                         height(t->right->left) - height(t->right->right) == -1)));
                if (height(t->right) - height(t->left) == 1) {
                    back_height(t);
                    return;
                } else if (height(t->right) == height(t->left)) {
                    t->father->height = max_height(t->father->left, t->father->right);
                    adjust(t->father, t->father->left == t ? left : right);
                    back_height(t);
                } else {
                    bool flag = height(t->right->left) != height(t->right->right);
                    if (height(t->right->left) > height(t->right->right)) {
                        rl(t);
                        adjust(t->father, t->father->left == t ? left : right);
                        back_height(t);
                        return;
                    }
                    rr(t);
                    t->father->height = max_height(t->father->left, t->father->right);
                    if (flag) {//??
                        adjust(t->father, t->father->left == t ? left : right);
                    }
                    back_height(t);
                }
            } else {
                assert(height(t->left) - height(t->right) == 1 || height(t->left) - height(t->right) == 0 ||
                       (height(t->left) - height(t->right) == 2 &&
                        (height(t->left->right) - height(t->left->left) == 1 ||
                         height(t->left->right) - height(t->left->left) == 0 ||
                         height(t->left->right) - height(t->left->left) == -1)));
                if (height(t->left) - height(t->right) == 1) {
                    back_height(t);
                    return;
                } else if (height(t->left) == height(t->right)) {
                    t->father->height = max_height(t->father->left, t->father->right);
                    adjust(t->father, t->father->left == t ? left : right);
                    back_height(t);
                } else {
                    bool flag = height(t->left->right) != height(t->left->left);
                    if (height(t->left->right) > height(t->left->left)) {
                        lr(t);
                        adjust(t->father, t->father->left == t ? left : right);
                        back_height(t);
                        return;
                    }
                    ll(t);
                    t->father->height = max_height(t->father->left, t->father->right);
                    if (flag) {
                        adjust(t->father, t->father->left == t ? left : right);
                    }
                    back_height(t);
                }
            }
        }

        static node *getll(node *_nd) {//得到最左的孩子
            if (_nd->left == nullptr)return _nd;
            return getll(_nd->left);
        }

        static node *getrr(node *_nd) {//得到最右的孩子
            if (_nd->right == nullptr)return _nd;
            return getrr(_nd->right);
        }

    public:

        /**
         * see BidirectionalIterator at CppReference for help.
         *
         * if there is anything wrong throw invalid_iterator.
         *     like it = map.begin(); --it;
         *       or it = map.end(); ++end();
         */
        class const_iterator;

        class iterator {
            friend map;
        private:

            node *rt = nullptr;
            node *nd = nullptr;

            iterator(node *_nd, node *_rt) {
                nd = _nd;
                rt = _rt;
            }
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            iterator() {
                // TODO
            }

            iterator(const iterator &other) {
                // TODO
                rt = other.rt;
                nd = other.nd;
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                if (nd == nullptr) {
                    throw invalid_iterator();
                }
                node *tmp = nd;
                if (nd->right != nullptr) {
                    nd = getll(nd->right);
                    return *this;
                }
                while (nd->father != nullptr && nd->father->right == nd) {
                    nd = nd->father;
                }
//                if (nd == rt) {
//                    throw invalid_iterator();
//                }
                nd = nd->father;
                return iterator(tmp, rt);
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                if (nd == nullptr) {
                    throw invalid_iterator();
                }
                if (nd->right != nullptr) {
                    nd = getll(nd->right);
                    return *this;
                }
                while (nd->father != nullptr && nd->father->right == nd) {
                    nd = nd->father;
                }
//                if (nd == rt) {
//                    throw invalid_iterator();
//                }

                nd = nd->father;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                node *tmp = nd;
                if (nd == nullptr) {
                    if (rt == nullptr)throw invalid_iterator();
                    nd = getrr(rt);
                    return iterator(tmp, rt);
                }
                if (nd->left != nullptr) {
                    nd = getrr(nd->left);
                    return *this;
                }
                while (nd->father != nullptr && nd->father->left == nd) {
                    nd = nd->father;
                }
                if (nd == rt) {
                    throw invalid_iterator();
                }
                nd = nd->father;
                return iterater(tmp, rt);
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                if (nd == nullptr) {
                    if (rt == nullptr)throw invalid_iterator();
                    nd = getrr(rt);
                    return *this;
                }
                if (nd->left != nullptr) {
                    nd = getrr(nd->left);
                    return *this;
                }
                while (nd->father != nullptr && nd->father->left == nd) {
                    nd = nd->father;
                }
                if (nd == rt) {
                    throw invalid_iterator();
                }
                nd = nd->father;
                return *this;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            value_type &operator*() const {
                return nd->val;
            }

            bool operator==(const iterator &rhs) const {
                return nd == rhs.nd && rt == rhs.rt;
            }

            bool operator==(const const_iterator &rhs) const {}

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return nd != rhs.nd || rt != rhs.rt;
            }

            bool operator!=(const const_iterator &rhs) const {}

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            value_type *operator->() const noexcept {
                return &(nd->val);
            }
        };

        class const_iterator {
            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
        private:
            // data members.
        public:
            const_iterator() {
                // TODO
            }

            const_iterator(const const_iterator &other) {
                // TODO
            }

            const_iterator(const iterator &other) {
                // TODO
            }
            // And other methods in iterator.
            // And other methods in iterator.
            // And other methods in iterator.
        };

        /**
         * TODO two constructors
         */
        map() {}

        map(const map &other) {
            if (root == other.root)return;
            clear(root);
            _size = other._size;
            copy(root, other.root);
        }

        /**
         * TODO assignment operator
         */
        map &operator=(const map &other) {
            if (root == other.root)return *this;
            clear(root);
            _size = other._size;
            copy(root, other.root);
            return *this;
        }

        /**
         * TODO Destructors
         */
        ~map() {
            clear(root);
        }

        /**
         * TODO
         * access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        T &at(const Key &key) {
            if (root == nullptr)throw index_out_of_bound();
            node *tmp = root->find(key);
            if (tmp == nullptr)throw index_out_of_bound();
            return tmp->get_t();
        }

        const T &at(const Key &key) const {
            if (root == nullptr)throw index_out_of_bound();
            node *tmp = root->find(key)->get_t();
            if (tmp == nullptr)throw index_out_of_bound();
            return tmp->get_t();
        }

        /**
         * TODO
         * access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        T &operator[](const Key &key) {
            if (root == nullptr) {
                _size++;
                return _insert(root, nullptr, key, T())->get_t();
            }
            node *tmp = root->find(key);
            if (tmp == nullptr) {
                _size++;
//                node ttmp(key, T());
                return _insert(root, nullptr, key, T())->get_t();
            } else return tmp->get_t();
        }

        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const T &operator[](const Key &key) const {
            return at(key);
        }

        /**
         * return a iterator to the beginning
         */
        iterator begin() {
            if (root == nullptr)return iterator(root, root);
            node *nd = getll(root);
            return iterator(nd, root);
        }

        const_iterator cbegin() const {}

        /**
         * return a iterator to the end
         * in fact, it returns past-the-end.
         */
        iterator end() {
            return iterator(nullptr, root);
//            if (root== nullptr)return iterator(root,root);
//            node* nd= getrr(root);
//            return iterator(nd,root);
        }

        const_iterator cend() const {}

        /**
         * checks whether the container is empty
         * return true if empty, otherwise false.
         */
        bool empty() const {
            return _size == 0;
        }

        /**
         * returns the number of elements.
         */

        size_t size() const {
            return _size;
        }

        /**
         * clears the contents
         */
        void clear() {
            clear(root);
            _size = 0;
        }

        /**
         * insert an element.
         * return a pair, the first of the pair is
         *   the iterator to the new element (or the element that prevented the insertion),
         *   the second one is true if insert successfully, or false.
         */
        pair<iterator, bool> insert(const value_type &value) {
            node *no = nullptr;
            node *tmp = root->find(value.first);
            if (tmp != nullptr)return pair<iterator, bool>(iterator(tmp, root), false);
            return pair<iterator, bool>(iterator(_insert(root, no, value.first, value.second), root), true);
        }

        /**
         * erase the element at pos.
         *
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         */
        void erase(iterator pos) {
            if (pos.rt != root || pos.nd == nullptr)throw invalid_iterator();
            remove(pos.nd, root);
        }

        /**
         * Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         * The default method of check the equivalence is !(a < b || b > a)
         */
        size_t count(const Key &key) const {
            node *nd = root->find(key);
            if (nd == nullptr)return 0;
            return 1;
        }

        /**
         * Finds an element with key equivalent to key.
         * key value of the element to search for.
         * Iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key) {
            node *nd = root->find(key);
            return iterator(nd, root);
        }

        const_iterator find(const Key &key) const {}
    };

}

#endif
