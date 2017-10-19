#ifndef PAGE_H
#define PAGE_H


class Page
{
    public:
        Page();
        Page(int refString, bool dirtyBit);
        virtual ~Page();

        void setRefString(int refString);

        void setDirtyBit(bool dirtyBit);

        int getRefString();

        bool getDirtyBit();

    protected:

    private:
        int refString;
        bool dirtyBit;
};

#endif // PAGE_H
