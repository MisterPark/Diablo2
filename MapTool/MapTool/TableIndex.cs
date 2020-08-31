using System;
using System.Collections.Generic;
using System.Text;

namespace MapTool
{
    struct TableIndex
    {
        public int row;
        public int col;

        public TableIndex(int row, int col)
        {
            this.row = row;
            this.col = col;
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
