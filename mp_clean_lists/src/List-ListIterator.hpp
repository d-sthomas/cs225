
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP3.1
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }
    ListIterator(ListNode* x, ListNode* t) : position_(x), tail_(t) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        // completed
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        // completed
        ListNode* tmp = position_;
        position_ = position_->next;
        return ListIterator(tmp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        // completed
        if (position_ != NULL) position_ = position_->prev;
        else position_ = tail_;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        // completed
        ListNode* tmp = position_;
        if (position_ != NULL) position_ = position_->prev;
        else position_ = tail_;
        return ListIterator(tmp);
        return ListIterator();
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
