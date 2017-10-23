#ifndef PAGE_H
#define PAGE_H

/**

Page is an unit that every time CPU reads the reference string to the queue.

Page has a reference string, a dirty bit and a reference bit.

*/

class Page
{
    public:
        Page();
        Page(int, bool);
        Page(int, bool, bool);
        virtual ~Page();

        // set reference string
        void setRefString(int);

        // get reference string
        int getRefString();

        // set dirty bit
        void setDirtyBit(bool);

        // get dirty bit
        bool getDirtyBit();

        // set reference bit
        void setRefBit(bool);

        // get reference bit
        bool getRefBit();

    protected:

    private:
        int refString;
        bool dirtyBit;
        bool refBit;
};

#endif // PAGE_H
