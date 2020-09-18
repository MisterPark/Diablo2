using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SpriteEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string filename = string.Empty;

            string saveDir = AppDomain.CurrentDomain.BaseDirectory;
            saveDir = saveDir + @"..\Worked";

            DirectoryInfo dir = new DirectoryInfo(saveDir);
            if (dir.Exists == false)
            {
                dir.Create();
            }

            OpenFileDialog dialog = new OpenFileDialog();
            dialog.InitialDirectory = dir.FullName;
            dialog.Multiselect = true;

            if (dialog.ShowDialog() != DialogResult.OK)
            {
                return;

            }

            Array.Sort(dialog.FileNames);
            
            if(radioButton1.Checked)
            {
                int imgW = Bitmap.FromFile(dialog.FileNames[0]).Width;
                int imgH = Bitmap.FromFile(dialog.FileNames[0]).Height;
                int count = dialog.FileNames.Length;
                Bitmap bmp = new Bitmap(imgW * count, imgH);
                Graphics g = Graphics.FromImage(bmp);

                for (int i = 0; i < count; i++)
                {
                    Image img = Bitmap.FromFile(dialog.FileNames[i]);
                    g.DrawImage(img, i * imgW, 0, imgW, imgH);
                    
                }

                pictureBox1.Image = bmp;
                pictureBox1.Width = bmp.Width;
                pictureBox1.Height = bmp.Height;
            }
            else
            {
                int imgW = Bitmap.FromFile(dialog.FileNames[0]).Width;
                int imgH = Bitmap.FromFile(dialog.FileNames[0]).Height;
                int count = dialog.FileNames.Length;
                Bitmap bmp = new Bitmap(imgW, imgH * count);
                Graphics g = Graphics.FromImage(bmp);

                for (int i = 0; i < count; i++)
                {
                    Image img = Bitmap.FromFile(dialog.FileNames[i]);
                    g.DrawImage(img, 0, i*imgH, imgW, imgH);

                }

                pictureBox1.Image = bmp;
                pictureBox1.Width = bmp.Width;
                pictureBox1.Height = bmp.Height;
            }

            
            textBox1.Text = dialog.SafeFileName;

            //pictureBox1.Image = Bitmap.FromFile(filename);
            //pictureBox1.Width = pictureBox1.Image.Width;
            //pictureBox1.Height = pictureBox1.Image.Height;
            //pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string saveDir = AppDomain.CurrentDomain.BaseDirectory;
            saveDir = saveDir + @"..\Sprites";

            DirectoryInfo dir = new DirectoryInfo(saveDir);
            if(dir.Exists == false)
            {
                dir.Create();
            }
            if(System.IO.Directory.Exists(saveDir))
            {
                Directory.CreateDirectory(saveDir);

                pictureBox1.Image.Save(saveDir + "\\" + textBox1.Text, ImageFormat.Png);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null) return;
            Bitmap bmp = new Bitmap(pictureBox1.Image);
            for (int x = 0; x < bmp.Width; x++) 
            {
                for (int y = 0; y < bmp.Height; y++) 
                {
                    Color color = bmp.GetPixel(x, y);
                    int sum = color.R + color.G + color.B;
                    if(sum < numericUpDown1.Value)
                    {
                        bmp.SetPixel(x, y, Color.Transparent);
                    }
                }
            }
            pictureBox1.Image = bmp;
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }
    }
}
