/*Aaron Skouby and Gerald Hu*/

#ifndef _MAP_H_
#define _MAP_H_

#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <iostream>  //added to test
#include <vector> //added to test
#include <string> //added to test
#include <cmath> //added to test

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Map ADT based on C++ map implemented with binary search tree
/// @ingroup MySTL
/// @tparam Key Key type
/// @tparam Value Value type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior.
////////////////////////////////////////////////////////////////////////////////
template<typename Key, typename Value>
class map {

  struct node;           ///< Forward declare node class
  template<typename>
    class map_iterator; ///< Forward declare iterator class

  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef Key key_type;      ///< Public access to Key type
    typedef Value mapped_type; ///< Public access to Value type
    typedef std::pair<const key_type, mapped_type>
      value_type;              ///< Entry type
    typedef map_iterator<value_type>
      iterator;                ///< Bidirectional iterator
    typedef map_iterator<const value_type>
      const_iterator;          ///< Const bidirectional iterator
    typedef std::reverse_iterator<iterator>
      reverse_iterator;        ///< Reverse bidirectional iterator
    typedef std::reverse_iterator<const_iterator>
      const_reverse_iterator;  ///< Const reverse bidirectional iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Constructor
    map() : root(new node()), sz(0) {
      root->expand();
    }
    /// @brief Copy constructor
    /// @param m Other map
    map(const map& m) : root(new node(*m.root)), sz(m.sz) {
    }
    /// @brief Destructor
    ~map() {
      delete root;
    }

    /// @brief Copy assignment
    /// @param m Other map
    /// @return Reference to self
    map& operator=(const map& m) {
      if(this != &m) {
        delete root;
        root = new node(*m.root);
        sz = m.sz;
      }
      return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

	
	/*Added for testing purposes*/
	void printTree() 
	{
		size_t theHeight = (root->left)->height; //height
		std::vector<std::string> ans(theHeight);
		printNode((root->left), 0, theHeight, ans);
		for(size_t x = 0; x<ans.size(); x++)
		{
			std::cout<<ans[x]<<std::endl;
		}
	}
	
	size_t printNode (node* n, size_t line, size_t height, std::vector<std::string>& ans)
	{
		size_t charUsed = 0; //for spacing
		size_t next = line+1;//index of where next number goes
		/*Left tree*/
		if ((n->left)->is_internal()) 
		{
			size_t space = printNode(n->left, next, height, ans);
			charUsed += space;
		}
		/* Middle */
		for (size_t x =0; x<charUsed; x++)
		{
			ans[line] += " ";
		}
		std::string s = "(" + std::to_string(n->value.first) + "," + n->value.second + ")";
		ans[line] += s;
		for (size_t x = line+1; x<ans.size(); x++)
		{
			for(size_t y =0; y<s.size(); y++)
			{
				ans[x]+= " ";
			}
		}
		charUsed += s.size();
		
		/*Right tree*/
		if ((n->right)->is_internal()) 
		{
			size_t space = printNode(n->right, next, height, ans);
			charUsed += space;
			for (size_t x = line; x < next; x++)
			{
				for (size_t y = 0; y < space; y++)
				{
					ans[x] +=" ";
				}
			}
		}
		return charUsed;
	}
	/*End Added for test purposes*/
	
	
    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return iterator(root->leftmost());}
    /// @return Iterator to end
    iterator end() {return iterator(root);}
    /// @return Iterator to reverse beginning
    reverse_iterator rbegin() {return reverse_iterator(root);}
    /// @return Iterator to reverse end
    reverse_iterator rend() {return reverse_iterator(root->leftmost());}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return const_iterator(root->leftmost());}
    /// @return Iterator to end
    const_iterator cend() const {return const_iterator(root);}
    /// @return Iterator to reverse beginning
    const_reverse_iterator crbegin() const {return const_reverse_iterator(root);}
    /// @return Iterator to reverse end
    const_reverse_iterator crend() const {return const_reverse_iterator(root->leftmost());}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of map
    size_t size() const {return sz;}
    /// @return Does the map contain anything?
    bool empty() const {return sz == 0;}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function should insert a new
    /// element with that key and return a reference to its mapped value
    /// (constructed through default construction)
    Value& operator[](const Key& k) {
      /// @todo implement at function. Utilize inserter function.
	  
	  iterator it = inserter(value_type(k, mapped_type())).first; //insert w/ key k and default value if not there
	  return it->second;
    }

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    Value& at(const Key& k) {
      /// @todo implement at function. Utilize find function.
	  iterator it = find(k);
	  if (it == end())
	  {
		throw std::out_of_range("Key doesn't Exist");//throw out of range exception  
	  }
	  else
	  {
		return it->second;
	  }
    }

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    const Value& at(const Key& k) const {
      /// @todo implement at function. Utilize find function.
      
	  //fine because don't edit in this function
	  iterator it = find(k);
	  if (it == cend())
	  {
		throw std::out_of_range("Key doesn't Exist");//throw out of range exception  
	  }
	  else
	  {
		return it->second;
	  }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Insert element into map, i.e., put(k, v) from the Map ADT
    /// @param v Key, Value pair
    /// @return pair of iterator and bool. Iterator pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Insert is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    std::pair<iterator, bool> insert(const value_type& v) {
      /// @todo Implement insert. Utilize inserter helper.
	  std::pair<node*, bool> ans = inserter(v); //gets answer from inserter
	  if (!ans.second) (ans.first)->replace(v); //if exists, replace value
      return std::make_pair(iterator(ans.first), ans.second); //returns ans except node changed to iterator
    }
    /// @brief Remove element at specified position
    /// @param position Position
    /// @return Position of new location of element which was after eliminated
    ///         one
    iterator erase(const_iterator position) {
    /// @todo this...
	  if (position != cend())
	  {
		node* temp = position.n; //extract node
		return iterator(eraser(temp)); //make type change explicit
	  }
	  return end(); //return end because they gave us cend and the return isn't constant
    }
    /// @brief Remove element at specified position
    /// @param k Key
    /// @return Number of elements removed (in this case it is at most 1)
    size_t erase(const Key& k) {
      /// @todo Implement erase. Utilize finder and eraser helpers.
      node* temp = finder(k); //find node with same key
	  if(temp->is_internal())
	  {
		eraser(temp);
		return 1; //element was deleted
	  }
	  else
	  {
		return 0; //no deletion
	  }
    }
    /// @brief Removes all elements
    void clear() noexcept {
      delete root;
      root = new node();
      root->expand();
      sz = 0;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Operations
    /// @{

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, end() otherwise
    iterator find(const Key& k) {
      //finder returns a node, so...
      //we convert the node return val to an iterator return val
      node* result = finder(k);
      if (result->is_internal())
      {
        return iterator(result);
      }
      else
      {
        return end();
      }
    }

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, cend() otherwise
    const_iterator find(const Key& k) const {
      /// @todo Implement find. Utilize the finder helper
      node* result = finder(k);
      if (result->is_internal())
      {
        return const_iterator(result);
      }
      else
      {
        return cend();
      }
    }

    /// @brief Count elements with specific keys
    /// @param k Key
    /// @return Count of elements with key \c k
    ///
    /// Because all elements in a map container are unique, the function will
    /// only return 1 or 0.
    size_t count(const Key& k) const {
      /// @todo Implement count. Utilize the find operation.
	  return !(find(k) == cend()); //1 if found 0 if not
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Helpers
    /// @{

    /// @brief Utility for finding a node with Key \c k
    /// @param k Key
    /// @return Node pointer to either where node exists or where it should be
    ///         inserted
    ///
    /// Base your algorithm off of Code Fragment 10.9 on page 436
    node* finder(const Key& k) const {
	  
	  node* curr = root->left;//tree is to left of the superroot
	  while (curr->is_internal() && k != (curr->value).first)
     //while isInternal is true, and k is not the value you're looking for
     //curr-value is a pair (standard library), and pair.first returns the first element of the pair
	  {
		  if (k > (curr->value).first)
		  {
			  curr = curr->right; //go right
		  }
		  else
		  {
			  curr = curr->left; //go left
		  }
	  }
      return curr; //where found or where should be
    }

    /// @brief Utility for inserting a new node into the data structure.
    /// @param v Key, Value pair
    /// @return pair of node and bool. node pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Inserter is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    ///
    /// Base you algorithm off of Code Fragment 10.10 on page 436
    ///
    /// Hint: Will need to use functions node::replace and node::expand
    std::pair<node*, bool> inserter(const value_type& v) {
      /// @todo Implement inserter helper function
	  
	  node* n = finder(v.first);
	  if (n->is_internal()) //already exists
	  {
		  return std::make_pair(n, false);
	  }
	  else //doesn't exist
	  {
		  n->replace(v); //give value
		  n->expand(); //give children
		  node* temp = n;
		  do
		  {
			temp->set_height(); //adjust node height
			temp = temp->parent;
		  }while(!temp->is_root());
		  sz++; //change size
		  n->rebalance(); //fix misbalances
		  return std::make_pair(n, true);
	  }
    }

    /// @brief Erase a node from the tree
    /// @param n Node to erase
    /// @return Next inorder successor of \c n in tree
    ///
    /// Base your algorithm off of Code Fragment 10.11 on page 437
    ///
    /// Hint: will need to use functions node::inorder_next or node::leftmost,
    /// node::replace, and node::remove_above_external
    node* eraser(node* n) {
      if (n->is_internal()) //else do nothing
      {
        //then node n exists, and we enter the next logic block
		node* ans = nullptr; //value to be returned (temporarily nullptr)
        if ((n->left)->is_external())
        {
          ans = (n->left)->remove_above_external(); //returns inorder next
        }
        else if ((n->right)->is_external())
        {
          ans = (n->right)->remove_above_external(); //returns inorder next
        }
        else
        {
          node* y = (n->right)->leftmost(); //is same a inorder next except doesn't go up
          node* x = y->left;
          n->replace(y->value);
          ans = x->remove_above_external(); //returns inorder next
        }
		sz--;
		ans->rebalance(); //fixes misbalances
		return ans;
      }
	  return n; //return external nodes (don't have anything else to do with them)
 
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Data
    /// @{

    node* root;     ///< Root of binary tree, the root will be a sentinel node
                    ///< for end iterator. root.left is the "true" root for the
                    ///< data
    size_t sz;      ///< Number of nodes

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Internal structure for binary search tree
    ////////////////////////////////////////////////////////////////////////////
    struct node {

      //////////////////////////////////////////////////////////////////////////
      /// @name Constructors
      /// @{

      /// @brief Constructor
      /// @param v Map entry (Key, Value) pair
      node(const value_type& v = value_type()) :
        value(v), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

      /// @brief Copy constructor
      /// @param n node to perform deep copy from
      node(const node& n) : value(n.value), parent(nullptr), left(nullptr), right(nullptr), height(n.height) {
		if (n.is_internal())
		{
			left = new node(*n.left);
			left->parent = this;
			right = new node(*n.right);
			right->parent = this;
		}
      }

      /// @brief Copy assignment - Deleted
      /// @param n Other node
      node& operator=(const node& n) = delete;

      /// @brief Destructor
      ~node() {
        delete left;
        delete right;
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Modifiers
      /// @{

      /// @brief Replace value of node, used for setting values on external
      ///        placeholder nodes
      /// @param v New value
      void replace(const value_type& v) {
        const_cast<Key&>(value.first) = v.first;
        value.second = v.second;
      }

      /// @brief Expand external node to make it internal
      void expand() {
        left = new node;
        right = new node;
        left->parent = this;
        right->parent = this;
      }

      /// @brief Remove above external node, assumes this is external node
      /// @return Sibling of \c n, who is promoted to n's parent's position
      node* remove_above_external() {
        node* par = parent;
        node* sib = this == par->left ? par->right : par->left;
        node* gpar = par->parent;
        if(par == gpar->left)
          gpar->left = sib;
        else
          gpar->right = sib;
        sib->parent = gpar;
        par->left = par->right = nullptr;
        delete this;
        delete par;
        if(sib->is_external())
          sib = sib->parent;
        return sib;
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Helpers for AVL trees
      /// @{

      /// @return Height of the node which is 0 for external node
      size_t get_height() {
        return this->is_external() ? 0: this->height;
      }

      /// @return Difference of heights of left and right children
      int height_diff() {
        return this->right->get_height() - this->left->get_height();
      }

      /// @brief Set the height as 1 added to the maximum height of its
      ///        children
      void set_height() {
        size_t hl = this->left->get_height();
        size_t hr = this->right->get_height();
        this->height = 1 + (hl > hr? hl : hr);
      }

      /// @return True when the height difference of the children nodes
      ///         does not exceed 1
      bool balanced() {
        int bal = height_diff();
        return ((-1<=bal)&&(bal<=1));
      }

      /// @brief Given a node this returns the tallest grandchild
      /// @return The grandchild with the maximum height
      node* tall_grand_child()  {
        node* l = left;
        node* r = right;
        // left child's height is greater than right child's height
        if(l->get_height() >= r->get_height())
          if(l->left->get_height() >= l->right->get_height())
            return l->left;
          else
            return l->right;
        // right child's height is greater than left child's height
        else
          if(r->right->get_height() >= r->left->get_height())
            return r->right;
          else
            return r->left;
      }

      /// @brief Rebalances the tree from the node to the root.
      ///        It sets the height of every node in the path to root.
      ///        On a disbalanced node, restructring is called to restore
      ///        the balance in the tree.
      /// Base your algorithm off of Code Fragment 10.17 on page 449 in book
      ///
      /// Hint: will need the functions balanced(), tall_grand_child(),
      ///       set_height()
      void rebalance() {
        /// @todo Implement resbalancing
		node* z = this; //looking for unbalanced node z
		while (!z->is_root())
		{
			if (!z->balanced()) 
			{
				z = (z->tall_grand_child())->restructure(); //function works on unbalanced node's tallest grandchild
			}
			z = z->parent;
			z->set_height(); //adjust heights as goes up
		}
      }

      /// @brief Restructuring the tri-node structure's balance where
      ///        the grandparent of the node is disbalanced.
      /// @return The tri-node structure after restructring
      ///
      /// Base your algorithm off of Code Fragment 10.12 on page 442 in book
      ///
      /// Hint: You can create your own supporting functions to implement
      ///       code reusability.
      node* restructure() {
        /// @todo Implement restructuring
		node* y = parent; //name so don't lose after rotate
		node* z = y->parent; //name so don't lose after rotate
		//x is "this"
		if (y == z->left) //larger on left
		{
			if (this == y->right) y->rotate_left(); //needs double rotate (2nd is larger on right)
			return z->rotate_right();
		}
		else //larger on right
		{
			if (this == y->left) y->rotate_right(); //needs double rotate (2nd is larger on left)
			return z->rotate_left();
		}
      }

      /// @brief Set new left and right children to a node
      /// @param New left and right children
      /// @return Node with the resetted children
      node* set_children(node* l, node *r)  {
        left = l;
        right = r;
        left->parent = this;
        right->parent = this;
        return this;
      }

      /// @brief Rotate right a node
      /// @return Node structure after right rotation
      node* rotate_right() {
        node* p = this;
        node* c = p->left;
        node* s = c->right;

        c->parent = p->parent;
        if(p == p->parent->left)
          p->parent->left = c;
        else
          p->parent->right = c;
        c->set_children(c->left,p);
        p->set_children(s,p->right);
        p->set_height();
        c->set_height();
        return c;
      }

      /// @brief Rotate left a node
      /// @return Node structure after left rotation
      node* rotate_left() {
        node* p = this;
        node* c = p->right;
        node* s = c->left;

        c->parent = p->parent;
        if(p == p->parent->left)
          p->parent->left = c;
        else
          p->parent->right = c;
        c->set_children(p,c->right);
        p->set_children(p->left,s);
        p->set_height();
        c->set_height();
        return c;
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Accessors
      /// @{

      /// @return If parent is null return true, else false
      bool is_root() const {return parent == nullptr;}
      /// @return If both children are null return true, else false
      bool is_external() const {return left == nullptr && right == nullptr;}
      /// @return If it is not external then it is internal
      bool is_internal() const {return !is_external();}

      /// @return Leftmost child of this node
      node* leftmost() const {
        const node* n = this;
        while(n->is_internal()) n = n->left;
        return n->parent;
      }

      /// @return Next node in the binary tree according to an inorder
      ///         traversal
      node* inorder_next() {
        //Here, I have a right child, so inorder successor is leftmost child
        //of right subtree
        if(right->is_internal()) {
          return right->leftmost();
        }
        //Otherwise, I am a right child myself and need to find an ancestor
        //who has a right child
        else {
          node* n = this;
          node* w = parent;
          while(n == w->right) {
            n = w;
            w = w->parent;
          }
          return w;
        }
      }

      /// @return Previous node in the binary tree according to an inorder
      ///         traversal
      node* inorder_prev() {
        //Here, I have a left child, so inorder predecessor is rightmost child
        //of left subtree
        if(left->is_internal()) {
          node* n = left;
          while(n->is_internal()) n = n->right;
          return n->parent;
        }
        //Otherwise, I am a left child myself and need to find an ancestor
        //who has a left child
        else {
          node* n = this;
          node* w = parent;
          while(n == w->left) {
            n = w;
            w = w->parent;
          }
          return w;
        }
      }

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Data
      /// @{

      value_type value; ///< Value is pair(key, value)
      node* parent;     ///< Parent node
      node* left;       ///< Left node
      node* right;      ///< Right node
      size_t height;    ///< Height of the node (used in AVL trees)

      /// @}
      //////////////////////////////////////////////////////////////////////////
    };

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Bidirectional iterator for a linked binary tree
    /// @tparam U value_type of map
    ////////////////////////////////////////////////////////////////////////////
    template<typename U>
      class map_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        public:
          //////////////////////////////////////////////////////////////////////
          /// @name Constructors
          /// @{

          /// @brief Construction
          /// @param v Pointer to position in binary tree
          map_iterator(node* v = NULL) : n(v) {}

          /// @brief Copy construction
          /// @param i Other iterator
          map_iterator(const map_iterator<typename std::remove_const<U>::type>& i) : n(i.n) {}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Comparison
          /// @{

          /// @brief Equality comparison
          /// @param i Iterator
          bool operator==(const map_iterator& i) const {return n == i.n;}
          /// @brief Inequality comparison
          /// @param i Iterator
          bool operator!=(const map_iterator& i) const {return n != i.n;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Dereference
          /// @{

          /// @brief Dereference operator
          U& operator*() const {return n->value;}
          /// @brief Dereference operator
          U* operator->() const {return &n->value;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Advancement
          /// @{

          /// @brief Pre-increment
          map_iterator& operator++() {n = n->inorder_next(); return *this;}
          /// @brief Post-increment
          map_iterator operator++(int) {map_iterator tmp(*this); ++(*this); return tmp;}
          /// @brief Pre-decrement
          map_iterator& operator--() {n = n->inorder_prev(); return *this;}
          /// @brief Post-decrement
          map_iterator operator--(int) {map_iterator tmp(*this); --(*this); return tmp;}

          /// @}
          //////////////////////////////////////////////////////////////////////

        private:
          node* n; ///< Map node

          friend class map;
      };

    /// @}
    ////////////////////////////////////////////////////////////////////////////

};

}

#endif