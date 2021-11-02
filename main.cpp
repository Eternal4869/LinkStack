/*
 * @Author: Eternal4869 
 * @Date: 2021-11-02 14:26:01 
 * @Last Modified by:   Eternal4869 
 * @Last Modified time: 2021-11-02 14:26:01 
 */
#include <iostream>
using namespace std;

//结点
template <class Elem>
struct Node
{
    Elem data;        //数据域
    Node<Elem> *next; //指针域

    Node() //无参情况下
    {
        next = nullptr;
    }

    //有参数的情况下
    Node(Elem item, Node<Elem> *link = nullptr) //后面的指针设置是防止无指针乱指
    {
        data = item;
        next = link;
    }
};

template <class Elem>
class LinkStack
{
private:
    Node<Elem> *top; //栈顶指针
    int count;       //元素个数
public:
    LinkStack();                                             //构造函数
    ~LinkStack();                                            //析构函数
    int Length() const;                                      //求栈长度
    bool Empty() const;                                      //判断栈是否为空
    void Clear();                                            //清空栈
    void Traverse() const;                                   //遍历栈
    bool Top(Elem &e) const;                                 //返回栈顶元素
    bool Push(const Elem &e);                                //将元素入栈
    bool Pop(Elem &e);                                       //将元素出栈
    LinkStack(const LinkStack<Elem> &copy);                  //复制构造函数
    LinkStack<Elem> &operator=(const LinkStack<Elem> &copy); //重载 = 符号
};

template <class Elem>
LinkStack<Elem>::LinkStack()
{
    top = nullptr;
    count = 0;
}

template <class Elem>
LinkStack<Elem>::~LinkStack()
{
    Clear();
}

template <class Elem>
int LinkStack<Elem>::Length() const
{
    return count;
}

template <class Elem>
bool LinkStack<Elem>::Empty() const
{
    return top == nullptr;
}

template <class Elem>
void LinkStack<Elem>::Clear()
{
    Elem e; //创建临时变量，用于存放删除数据
    while (top != nullptr)
    {
        Pop(e); //栈顶非空时，元素依次出栈
    }
}

template <class Elem>
void LinkStack<Elem>::Traverse() const
{
    LinkStack<Elem> tStack; //创建临时栈，用于输出
    Node<Elem> *tPtr;       //创建临时指针（循环用）
    //遍历原栈(从顶到底),把数据逆向传给临时栈
    for (tPtr = top; tPtr != nullptr; tPtr = tPtr->next)
    {
        tStack.Push(tPtr->data); //数据入栈
    }
    //遍历临时栈，输出数据
    for (tPtr = tStack.top; tPtr != nullptr; tPtr = tPtr->next)
    {
        cout << tPtr->data << endl;
    }
}

template <class Elem>
bool LinkStack<Elem>::Pop(Elem &e)
{
    if (Empty()) //如果栈空，则不可操作
    {
        return false;
    }
    else //栈非空
    {
        Node<Elem> *old_top = top;
        e = old_top->data;
        top = old_top->next;
        delete old_top;
        count--;
        return true;
    }
}

template <class Elem>
bool LinkStack<Elem>::Top(Elem &e) const
{
    if (top == nullptr) //如果栈顶为空，则无法进行取栈顶操作
    {
        return false;
    }
    else //如果栈顶非空，则进行取栈顶操作
    {
        e = top->data; //用e来返回栈顶元素
        return true;
    }
}

template <class Elem>
bool LinkStack<Elem>::Push(const Elem &e)
{
    Node<Elem> *newTop = new Node<Elem>(e, top); //创建新栈顶指针
    if (newTop == nullptr)                       //动态内存耗尽
    {
        return false;
    }
    else
    {
        top = newTop;
        count++;
        return true;
    }
}

template <class Elem>
LinkStack<Elem>::LinkStack(const LinkStack<Elem> &copy)
//由栈copy构造一个新栈-复制构造函数
{
    if (copy.Empty()) //如果copy为空栈
    {
        top = nullptr;
        count = 0;
    }
    else //copy非空，复制栈
    {
        top = new Node<Elem>(copy.top->data); //生成当前栈顶
        count = copy.count;                   //复制栈元素个数
        Node<Elem> *tPtr = top;               //记录栈底位置
        //从栈顶向下遍历
        for (Node<Elem> *t = copy.top->next; t != nullptr; t = t->next)
        {
            tPtr->next = new Node<Elem>(t->data); //向栈顶下方增加元素
            tPtr = tPtr->next;                    //记录栈底位置
        }
    }
}

int main()
{
    LinkStack<int> ls1;
    cout << "Please enter integers : " << endl;
    int tmp, t;
    cin >> tmp;
    ls1.Push(tmp);
    cout << "Please enter integers : " << endl;
    cin >> tmp;
    ls1.Top(t);
    while (tmp > t)
    {
        ls1.Push(tmp);
        cout << "Please enter integers : " << endl;
        cin >> tmp;
        ls1.Top(t);
    }
    cout << "Stop!It's wrong!" << endl;
    cout << "Here are the right numbers:" << endl;
    ls1.Traverse();
    return 0;
}
