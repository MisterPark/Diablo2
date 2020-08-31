﻿using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;


namespace MapTool
{
    class RenderManager
    {
        // 멤버
        private static RenderManager instance = new RenderManager();
        private Device device = null;
        private Sprite sprite = null;
        private Line line = null;
        private Dictionary<string, SpriteImage> spriteMap = new Dictionary<string, SpriteImage>();
        // 프로퍼티
        public static RenderManager Instance
        {
            get { return instance; }
            private set { }
        }
 
        // 생성자
        private RenderManager()
        {
        }

        // 메소드
        public static void Initialize(Control target)
        {
            PresentParameters pp = new PresentParameters();
            pp.Windowed = true;
            pp.SwapEffect = SwapEffect.Discard;
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = DepthFormat.D16;
            instance.device = new Device(0, DeviceType.Hardware, target, CreateFlags.SoftwareVertexProcessing, pp);

            instance.sprite = new Sprite(instance.device);
            instance.line = new Line(instance.device);
        }

        public static void Clear()
        {
            instance.device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Blue, 1.0f, 0);
            instance.device.BeginScene();
        }
        public static void Present(Control target)
        {
            instance.device.EndScene();
            instance.device.Present(target);
        }

        public static void LoadSprite(string path, string key, TableIndex range)
        {
            Texture texture = TextureLoader.FromFile(instance.device, Application.StartupPath+ path);
            if (texture == null) return;

            SpriteImage image = new SpriteImage();
            image.texture = texture;
            image.imageInfo = TextureLoader.ImageInformationFromFile(Application.StartupPath + path);
            image.range = range;
            instance.spriteMap.Add(key, image);
        }

        public static void DrawSprite(string key, MyTransform trans, TableIndex index)
        {
            SpriteImage image = null;
            if(instance.spriteMap.TryGetValue(key, out image) == false)
            {
                return;
            }

            int w = image.imageInfo.Width / image.range.col;
            int h = image.imageInfo.Height / image.range.row;
            int x = index.col * w;
            int y = index.row * h;
            Rectangle rect = new Rectangle();
            rect.X = x;
            rect.Y = y;
            rect.Width = w;
            rect.Height = h;

            Matrix world, pos, rot, scale;
            pos = Matrix.Translation(trans.position + Camera.Instance.transform.position);
            rot = Matrix.RotationZ(trans.rotation.Z);
            scale = Matrix.Scaling(trans.scale);

            world = scale * rot * pos;
            
            instance.sprite.Begin(SpriteFlags.AlphaBlend);
            instance.sprite.Transform = world;
            instance.sprite.Draw(image.texture, rect, new Vector3(0, 0, 0), new Vector3(0, 0, 0), Color.FromArgb(255, 255, 255, 255));
            instance.sprite.End();
        }

        public static void DrawLine(float sx, float sy, float ex, float ey)
        {
            Vector2[] points = new Vector2[2];
            points[0].X = sx;
            points[0].Y = sy;
            points[1].X = ex;
            points[1].Y = ey;

            instance.line.Begin();
            instance.line.Draw(points, Color.Black);
            instance.line.End();
        }

        public static void DrawLine(float sx, float sy, float ex, float ey, Color color)
        {
            Vector2[] points = new Vector2[2];
            points[0].X = sx;
            points[0].Y = sy;
            points[1].X = ex;
            points[1].Y = ey;

            instance.line.Begin();
            instance.line.Draw(points, color);
            instance.line.End();
        }

    }
}
