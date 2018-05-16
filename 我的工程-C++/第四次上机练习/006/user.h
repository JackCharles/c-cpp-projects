
//user.h
#ifndef USER_H
#define USER_H

class Share
{
public:
    Share(int num):mData(num) {}
    int     getData() const
    {
        return mData;
    }
    void    setData(int data)
    {
        mData = data;
    }
private:
    int mData;
};



class User
{
public:
    User(int num = 0);
    ~User();
    User(const User& rhs);
    User& operator=(const User& rhs);
    void display(const char * objName) const;
    int  getData() const;
    void setData(int data);
private:
    void addRef();
    void releaseRef();
private:
    Share * objShared;
    int   * refCount;
};

#endif // USER_H

