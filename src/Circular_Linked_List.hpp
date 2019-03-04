#pragma once

template <typename T>
struct Node
{
	T data;
	Node<T> *next;

	Node<T>() : next(nullptr) {}
	Node<T>(const T &data) : data(data), next(nullptr) {}
	Node<T>(const T &data, Node<T> *next) : data(data), next(next) {}
};

template<typename T>
class Circular_Linked_List
{
public:

    T getTraveller()
    {
        return traveller->data;
    }

    void moveTravellerOneForward()
    {
        traveller = traveller->next;
    }

    void add(const T &new_contents)
    {
        if (head == nullptr)
        {
            head = new Node<T>(new_contents);
            head->next = head;
            last_thing_added = head;
            traveller = head;
        }
        else
        {
            Node<T> *new_node = new Node<T>(new_contents, head);
            last_thing_added->next = new_node;
            last_thing_added = new_node;
        }
    }

private:
    Node<T> *head = nullptr;
    Node<T> *last_thing_added = nullptr;
    Node<T> *traveller = nullptr;
};
