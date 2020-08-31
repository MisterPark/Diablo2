using System;
using System.Collections.Generic;
using System.Text;

namespace MapTool
{
    class Camera
    {
        private static Camera instanse = new Camera();
        public MyTransform transform = new MyTransform();
        public static Camera Instance
        {
            get { return instanse; }
            private set { }
        }
        public static float X 
        { 
            get { return instanse.transform.position.X; }
            set { instanse.transform.position.X = value; }
        }
        public static float Y 
        { 
            get { return instanse.transform.position.Y; } 
            set { instanse.transform.position.Y = value; } 
        }

        private Camera()
        {

        }

    }
}
