#ifndef PAGE_H
#define PAGE_H


class Page
{
    public:
        Page();
        Page(int, bool);
        Page(int, bool, bool);
        virtual ~Page();

        void setRefString(int);

        int getRefString();

        void setDirtyBit(bool);

        bool getDirtyBit();

        void setRefBit(bool);

        bool getRefBit();

    protected:

    private:
        int refString;
        bool dirtyBit;
        bool refBit;
};

#endif // PAGE_H
