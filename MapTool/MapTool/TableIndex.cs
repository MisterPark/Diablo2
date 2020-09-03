using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace MapTool
{
    class TableIndex : IComparable
    {
        public int row;
        public int col;

        public TableIndex(int row, int col)
        {
            this.row = row;
            this.col = col;
        }

        public int CompareTo(object obj) 
        {
            TableIndex comparand = obj as TableIndex;
            if (comparand == null)
            {
                throw new ApplicationException("TableIndex 개체가 아닙니다.");
            }
            return Compare(this, comparand);
        }
        public int Compare(object a,object b)
        {
            TableIndex ca = a as TableIndex;
            TableIndex cb = b as TableIndex;

            if(ca.row == cb.row)
            {
                
                if(ca.col < cb.col)
                {
                    return -1;
                }
                else if( ca.col > cb.col)
                {
                    return 1;
                }

                return 0;
            }
            else
            {
                if(ca.row < cb.row)
                {
                    return -1;
                }

                return 1;
            }

        }

        public static bool operator <(TableIndex lValue, TableIndex rValue)
        {
            if (lValue.row != rValue.row)
            {
                return lValue.row < rValue.row;
            }
            return lValue.col < rValue.col;
        }

        public static bool operator >(TableIndex lValue, TableIndex rValue)
        {
            if (lValue.row != rValue.row)
            {
                return lValue.row > rValue.row;
            }
            return lValue.col > rValue.col;
        }
    }
}
