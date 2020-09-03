using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;


namespace MapTool
{
    public enum SpriteType
    {
        NONE,
        ACT1_TOWN_FLOOR,
        ACT1_OUTDOOR_FLOOR,
        ACT1_TOWN_FENCE,

        SO_BW,
        SO_NU_HTH,
    }

    class RenderManager
    {
        // 멤버
        private static RenderManager instance = new RenderManager();
        private Device device = null;
        private Sprite sprite = null;
        private Line line = null;
        private Dictionary<SpriteType, SpriteImage> spriteMap = new Dictionary<SpriteType, SpriteImage>();
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
            //pp.EnableAutoDepthStencil = true;
            //pp.AutoDepthStencilFormat = DepthFormat.D16;
            instance.device = new Device(0, DeviceType.Hardware, target, CreateFlags.HardwareVertexProcessing, pp);
         
            instance.sprite = new Sprite(instance.device);
            instance.line = new Line(instance.device);
        }

        public static void Clear()
        {
            instance.device.Clear(ClearFlags.Target, Color.Blue, 0.0f, 0);
            instance.device.BeginScene();
        }
        public static void Present(Control target)
        {
            instance.device.EndScene();
            instance.device.Present(target);
        }

        public static void Present(Control target, int width,int height)
        {
            instance.device.EndScene();
            instance.device.Present(new Rectangle(0, 0, width, height), target, false);
        }


        public static void LoadSprite(string path, SpriteType key, TableIndex range)
        {
            ImageInformation imageInfo = TextureLoader.ImageInformationFromFile(Application.StartupPath + path);

            Texture texture = TextureLoader.FromFile(
                instance.device,
                Application.StartupPath + path,
                imageInfo.Width,
                imageInfo.Height,
                imageInfo.MipLevels,
                0,
                imageInfo.Format,
                Pool.Managed,
                Filter.None,
                Filter.None,
                0);
            if (texture == null) return;

            SpriteImage image = new SpriteImage();
            image.texture = texture;
            image.imageInfo = imageInfo;
            image.range = range;
            instance.spriteMap.Add(key, image);
        }

        public static SpriteImage GetSpriteImage(SpriteType key)
        {
            SpriteImage img = null;
            if(instance.spriteMap.TryGetValue(key, out img))
            {
                return img;
            }

            return null;
        }

        public static void DrawSprite(SpriteType key, MyTransform trans, TableIndex index)
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

            Matrix world, pos, scale;
            Vector3 vpos = trans.position;
            vpos.Y -= (h - Tile.Height);
            pos = Matrix.Translation(vpos - Camera.Instance.transform.position);
            scale = Matrix.Scaling(trans.scale);

            world = scale * pos;
            
            instance.sprite.Begin(SpriteFlags.AlphaBlend);
            instance.sprite.Transform = world;
            instance.sprite.Draw(image.texture, rect, new Vector3(0, 0, 0), new Vector3(0, 0, 0), Color.FromArgb(255, 255, 255, 255));
            instance.sprite.End();
        }

        public static void DrawSprite(SpriteType key, MyTransform trans, TableIndex index, float ratio)
        {
            SpriteImage image = null;
            if (instance.spriteMap.TryGetValue(key, out image) == false)
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

            Matrix world, pos, scale;
            Vector3 vpos = trans.position;
            Vector3 vscale;
            vpos.Y -= (h - Tile.Height);
            vpos *= ratio;
            vscale = trans.scale * ratio;
            pos = Matrix.Translation(vpos);
            scale = Matrix.Scaling(vscale);
            
            world = scale * pos;

            instance.sprite.Begin(SpriteFlags.AlphaBlend);
            instance.sprite.Transform = world;
            instance.sprite.Draw(image.texture, rect, new Vector3(0, 0, 0), new Vector3(0, 0, 0), Color.FromArgb(255, 255, 255, 255));
            instance.sprite.End();
        }

        public static void DrawSubTileSprite(SpriteType key, MyTransform trans, TableIndex index)
        {
            SpriteImage image = null;
            if (instance.spriteMap.TryGetValue(key, out image) == false)
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

            Matrix world, pos, scale;
            pos = Matrix.Translation(trans.position - Camera.Instance.transform.position);
            scale = Matrix.Scaling(trans.scale);

            world = scale * pos;

            instance.sprite.Begin(SpriteFlags.AlphaBlend);
            instance.sprite.Transform = world;
            instance.sprite.Draw(image.texture, rect, new Vector3(0, h-Tile.Height, 0), new Vector3(0, 0, 0), Color.FromArgb(255, 255, 255, 255));
            instance.sprite.End();
        }

        public static void DrawImage(SpriteType key, MyTransform trans, TableIndex index)
        {
            SpriteImage image = null;
            if (instance.spriteMap.TryGetValue(key, out image) == false)
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

            Matrix world, pos, scale;
            pos = Matrix.Translation(trans.position);
            scale = Matrix.Scaling(trans.scale);

            world = scale * pos;

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

        public static void DrawLine(float sx, float sy, float ex, float ey, float ratio)
        {
            Vector2[] points = new Vector2[2];
            points[0].X = sx * ratio;
            points[0].Y = sy * ratio;
            points[1].X = ex * ratio;
            points[1].Y = ey * ratio;

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

        public static void DrawLine(float sx, float sy, float ex, float ey, float ratio, Color color)
        {
            Vector2[] points = new Vector2[2];
            points[0].X = sx * ratio;
            points[0].Y = sy * ratio;
            points[1].X = ex * ratio;
            points[1].Y = ey * ratio;

            instance.line.Begin();
            instance.line.Draw(points, color);
            instance.line.End();
        }

    }
}
