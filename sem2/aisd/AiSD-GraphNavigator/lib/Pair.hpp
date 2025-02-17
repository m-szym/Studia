#include <stdexcept>
#include <initializer_list>


template <typename L, typename R>
class Pair
{
private:
    L left;
    R right

    // empty constructor
    public : Pair()
        : left(), right()
    {
    }

    // normal constructor
    Pair(L _left, R _right)
        : left(_left), right(_right)
    {
    }
    
    // initializer list constructor
    Pair(std::initializer_list<L> initList)
        : left(initList[0]), right(initList[1])
    {
    }
    
    // copy constructor
    Pair(const Pair<L, R> &other)
        : left(other.left), right(other.right)
    {
    }
    
    // copy-swap assignment
    Pair &operator=(const Pair<L, R> &other)
    {
        left = other.left;
        right = other.right;
        return *this;
    }
    
    // move constructor
    Pair(Pair<L, R> &&other)
    {
        left = other.left;
        right = other.right;
        other.left = nullptr;
        other.right = nullptr;
    }
    
    // move assignment
    Pair &operator=(Pair<L, R> &&other)
    {
        left = other.left;
        right = other.right;
        other.left = nullptr;
        other.right = nullptr;
        return *this;
    }
    
    ~Pair()
    {
        delete left;
        delete right;
    }

    void setLeft(L newLeft)
    {
        left = newLeft;
    }

    void setRight(R newRight)
    {
        right = newRight;
    }

    void setBoth(L newLeft, R newRight)
    {
        left = newLeft;
        right = newRight;
    }

    L getLeft()
    {
        return left;
    }

    R getRight()
    {
        return right;
    }

    void print(std::ostream &os) const
    {
        os << left << " : " << right;
    }
};

template <typename L, typename R>
std::ostream &operator<<(std::ostream &os, const Pair<L, R> &pair)
{
    pair.print(os);
    return os;
}
