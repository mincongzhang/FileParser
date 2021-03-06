//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86
//http://rextester.com/l/cpp_online_compiler_visual

# include <boost/iterator/iterator_facade.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

struct node_base
{
    node_base() : m_next(0) {}

    // Each node manages all of its tail nodes
    virtual ~node_base() { delete m_next; }

    // Access the rest of the list
    node_base* next() const { return m_next; }

    // print to the stream
    virtual void print(std::ostream& s) const = 0;

    // double the value
    virtual void double_me() = 0;

    void append(node_base* p)
    {
        if (m_next)
            m_next->append(p);
        else
            m_next = p;
    }

 private:
    node_base* m_next;
};

template <class T>
struct node : node_base
{
    node(T x)
      : m_value(x)
    {}

    void print(std::ostream& s) const { s << this->m_value; }
    void double_me() { m_value += m_value; }

 private:
    T m_value;
};

class node_iterator
  : public boost::iterator_facade<
        node_iterator
      , node_base
      , boost::forward_traversal_tag
    >
{
 public:
    node_iterator()
      : m_node(0) {}

    explicit node_iterator(node_base* p)
      : m_node(p) {}

 private:
    friend class boost::iterator_core_access;

    void increment() { m_node = m_node->next(); }

    bool equal(node_iterator const& other) const
    {
        return this->m_node == other.m_node;
    }

    node_base& dereference() const { return *m_node; }

    node_base* m_node;
};

inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}

int main()
{
    std::auto_ptr<node<int> > nodes(new node<int>(42));
    nodes->append(new node<std::string>(" is greater than "));
    nodes->append(new node<int>(13));

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, " ")
    );
    std::cout << std::endl;
    
    for(node_iterator it(nodes.get());it!=node_iterator(); ++it ){
        std::cout<<"printing"<<std::endl;
        std::cout<<*it<<std::endl;
    }
    
    std::for_each(
        node_iterator(nodes.get()), node_iterator()
      , std::mem_fun_ref(&node_base::double_me)
    );

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, "/")
    );
    std::cout << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Base class only, without template
////////////////////////////////////////////////////////////////////////////////

//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86
# include <boost/iterator/iterator_facade.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

struct node_base
{
    virtual ~node_base() { delete m_next; }

    // Access the rest of the list
    node_base* next() const { return m_next; }

    node_base(int x) : m_value(x), m_next(0){}

    void print(std::ostream& s) const { s << this->m_value; }
    void double_me() { m_value += m_value; }
    void append(node_base* p)
    {
        if (m_next)
            m_next->append(p);
        else
            m_next = p;
    }
    
 private:
    int m_value;
    node_base* m_next;
};

class node_iterator
  : public boost::iterator_facade<
        node_iterator
      , node_base
      , boost::forward_traversal_tag
    >
{
 public:
    node_iterator()
      : m_node(0) {}

    explicit node_iterator(node_base* p)
      : m_node(p) {}

 private:
    friend class boost::iterator_core_access;

    void increment() { m_node = m_node->next(); }

    bool equal(node_iterator const& other) const
    {
        return this->m_node == other.m_node;
    }

    node_base& dereference() const { return *m_node; }

    node_base* m_node;
};

inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}

int main()
{
    std::auto_ptr<node_base > nodes(new node_base(42));
    nodes->append(new node_base(24));
    nodes->append(new node_base(13));

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, " ")
    );
    std::cout << std::endl;
    
    for(node_iterator it(nodes.get());it!=node_iterator(); ++it ){
        std::cout<<"printing"<<std::endl;
        std::cout<<*it<<std::endl;
    }
    
    std::for_each(
        node_iterator(nodes.get()), node_iterator()
      , std::mem_fun_ref(&node_base::double_me)
    );

    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, "/")
    );
    std::cout << std::endl;
}
