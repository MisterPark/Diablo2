using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System;
using System.Collections.Generic;
using System.Text;

namespace MapTool
{
    class MyTransform
    {
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;

        public MyTransform()
        {
            position.X = 0;
            position.Y = 0;
            position.Z = 0;
            rotation.X = 0;
            rotation.Y = 0;
            rotation.Z = 0;
            scale.X = 0;
            scale.Y = 0;
            scale.Z = 0;
        }
    }
}
