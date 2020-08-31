namespace MapTool
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.bottomPanel = new System.Windows.Forms.Panel();
            this.tileIndexLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.panelPosLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.screenPosLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.LeftPanel = new System.Windows.Forms.Panel();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.miniPanel = new System.Windows.Forms.Panel();
            this.controlPanel = new System.Windows.Forms.Panel();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.centerPanel = new System.Windows.Forms.Panel();
            this.mainPanel = new System.Windows.Forms.Panel();
            this.bottomPanel.SuspendLayout();
            this.LeftPanel.SuspendLayout();
            this.centerPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // bottomPanel
            // 
            this.bottomPanel.BackColor = System.Drawing.SystemColors.Highlight;
            this.bottomPanel.Controls.Add(this.tileIndexLabel);
            this.bottomPanel.Controls.Add(this.label4);
            this.bottomPanel.Controls.Add(this.panelPosLabel);
            this.bottomPanel.Controls.Add(this.label2);
            this.bottomPanel.Controls.Add(this.screenPosLabel);
            this.bottomPanel.Controls.Add(this.label1);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.bottomPanel.Location = new System.Drawing.Point(0, 420);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(800, 30);
            this.bottomPanel.TabIndex = 1;
            // 
            // tileIndexLabel
            // 
            this.tileIndexLabel.AutoSize = true;
            this.tileIndexLabel.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.tileIndexLabel.ForeColor = System.Drawing.Color.FloralWhite;
            this.tileIndexLabel.Location = new System.Drawing.Point(553, 9);
            this.tileIndexLabel.Name = "tileIndexLabel";
            this.tileIndexLabel.Size = new System.Drawing.Size(10, 12);
            this.tileIndexLabel.TabIndex = 5;
            this.tileIndexLabel.Text = ".";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label4.ForeColor = System.Drawing.Color.FloralWhite;
            this.label4.Location = new System.Drawing.Point(461, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "TileIndex : ";
            // 
            // panelPosLabel
            // 
            this.panelPosLabel.AutoSize = true;
            this.panelPosLabel.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.panelPosLabel.ForeColor = System.Drawing.Color.FloralWhite;
            this.panelPosLabel.Location = new System.Drawing.Point(292, 9);
            this.panelPosLabel.Name = "panelPosLabel";
            this.panelPosLabel.Size = new System.Drawing.Size(10, 12);
            this.panelPosLabel.TabIndex = 3;
            this.panelPosLabel.Text = ".";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label2.ForeColor = System.Drawing.Color.FloralWhite;
            this.label2.Location = new System.Drawing.Point(204, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "PanelPos : ";
            // 
            // screenPosLabel
            // 
            this.screenPosLabel.AutoSize = true;
            this.screenPosLabel.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.screenPosLabel.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.screenPosLabel.Location = new System.Drawing.Point(104, 9);
            this.screenPosLabel.Name = "screenPosLabel";
            this.screenPosLabel.Size = new System.Drawing.Size(10, 12);
            this.screenPosLabel.TabIndex = 1;
            this.screenPosLabel.Text = ".";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.ForeColor = System.Drawing.Color.FloralWhite;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "SceenPos : ";
            // 
            // LeftPanel
            // 
            this.LeftPanel.Controls.Add(this.splitter2);
            this.LeftPanel.Controls.Add(this.miniPanel);
            this.LeftPanel.Controls.Add(this.controlPanel);
            this.LeftPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.LeftPanel.Location = new System.Drawing.Point(520, 0);
            this.LeftPanel.Name = "LeftPanel";
            this.LeftPanel.Size = new System.Drawing.Size(280, 420);
            this.LeftPanel.TabIndex = 10;
            // 
            // splitter2
            // 
            this.splitter2.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.splitter2.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter2.Location = new System.Drawing.Point(0, 178);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(280, 10);
            this.splitter2.TabIndex = 13;
            this.splitter2.TabStop = false;
            // 
            // miniPanel
            // 
            this.miniPanel.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.miniPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.miniPanel.Location = new System.Drawing.Point(0, 0);
            this.miniPanel.Name = "miniPanel";
            this.miniPanel.Size = new System.Drawing.Size(280, 178);
            this.miniPanel.TabIndex = 12;
            // 
            // controlPanel
            // 
            this.controlPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.controlPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.controlPanel.Location = new System.Drawing.Point(0, 0);
            this.controlPanel.Name = "controlPanel";
            this.controlPanel.Size = new System.Drawing.Size(280, 420);
            this.controlPanel.TabIndex = 11;
            // 
            // splitter1
            // 
            this.splitter1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Right;
            this.splitter1.Location = new System.Drawing.Point(510, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(10, 420);
            this.splitter1.TabIndex = 11;
            this.splitter1.TabStop = false;
            // 
            // centerPanel
            // 
            this.centerPanel.Controls.Add(this.mainPanel);
            this.centerPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.centerPanel.Location = new System.Drawing.Point(0, 0);
            this.centerPanel.Name = "centerPanel";
            this.centerPanel.Size = new System.Drawing.Size(510, 420);
            this.centerPanel.TabIndex = 12;
            // 
            // mainPanel
            // 
            this.mainPanel.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.mainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPanel.Location = new System.Drawing.Point(0, 0);
            this.mainPanel.Name = "mainPanel";
            this.mainPanel.Size = new System.Drawing.Size(510, 420);
            this.mainPanel.TabIndex = 6;
            this.mainPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.mainPanel_MouseDown);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.centerPanel);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.LeftPanel);
            this.Controls.Add(this.bottomPanel);
            this.Name = "Form1";
            this.Text = "MapTool";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.bottomPanel.ResumeLayout(false);
            this.bottomPanel.PerformLayout();
            this.LeftPanel.ResumeLayout(false);
            this.centerPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel bottomPanel;
        private System.Windows.Forms.Label tileIndexLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label panelPosLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label screenPosLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel LeftPanel;
        private System.Windows.Forms.Splitter splitter2;
        private System.Windows.Forms.Panel miniPanel;
        private System.Windows.Forms.Panel controlPanel;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Panel centerPanel;
        private System.Windows.Forms.Panel mainPanel;
    }
}

