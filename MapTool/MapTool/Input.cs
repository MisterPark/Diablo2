using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace MapTool
{
    class Input
    {
        [DllImport("user32")]
        public static extern UInt16 GetAsyncKeyState(Int32 vKey);

        public static Input instance = new Input();

        private Input()
        {

        }

        

        public static bool IsKeyDown(Keys keyCode)
        {
            int vk = (int)keyCode;

            return ((GetAsyncKeyState(vk) & 0x0001) != 0);
        }

        public static bool IsKeyPress(Keys keyCode)
        {
            int vk = (int)keyCode;

            return ((GetAsyncKeyState(vk) & 0x8001) != 0);
        }

        public static void Update()
        {
            if (Input.IsKeyDown(Keys.W))
            {
                Camera.Y -= 10;
            }
            if (Input.IsKeyDown(Keys.A))
            {
                Camera.X -= 10;
            }
            if (Input.IsKeyDown(Keys.S))
            {
                Camera.Y += 10;
            }
            if (Input.IsKeyDown(Keys.D))
            {
                Camera.X += 10;
            }
            if(Input.IsKeyDown(Keys.Q))
            {
                Camera.X = 0;
                Camera.Y = 0;
            }
        }
    }
}
