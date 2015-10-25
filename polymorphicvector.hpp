#ifndef POLYMORPHICVECTOR_HPP
#define POLYMORPHICVECTOR_HPP

#include <experimental/any>
#include <vector>

class AbstractPolymorphicVector {
public:
    AbstractPolymorphicVector() = default;

    virtual void increaseSize() = 0;

    virtual std::experimental::any &getRefVector() = 0;

    virtual ~AbstractPolymorphicVector() = default;
};

template<typename T>
class PolymorphicVector final : public AbstractPolymorphicVector {
public:
    PolymorphicVector(std::size_t baseSize) :
        mVector(std::vector<T>(baseSize, T())) {}

    void increaseSize() {
        mRefVector.emplace_back(T());
    }

    std::experimental::any &getRefVector() {
        return mVector;
    }

    ~PolymorphicVector() = default;

private:
    std::experimental::any mVector;
    std::vector<T> &mRefVector = std::experimental::any_cast<std::vector<T>&>(mVector);
};

#endif // POLYMORPHICVECTOR_HPP

