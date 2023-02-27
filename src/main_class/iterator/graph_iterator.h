

template<typename T>
class OwnIterator: public std::iterator<std::input_iterator_tag, T>
{
    friend class OwnContainer;
private:
    OwnIterator(ValueType* p);
public:
    OwnIterator(const OwnIterator &it);

    bool operator!=(OwnIterator const& other) const;
    bool operator==(OwnIterator const& other) const; //need for BOOST_FOREACH
    typename OwnIterator::reference operator*() const;
    OwnIterator& operator++();
private:
    ValueType* p;
};
