namespace regulacja_swiatla
{
    partial class Form1
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.butSend = new System.Windows.Forms.Button();
            this.pbStatus = new System.Windows.Forms.PictureBox();
            this.labStatus = new System.Windows.Forms.Label();
            this.numericSend = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.pbStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericSend)).BeginInit();
            this.SuspendLayout();
            // 
            // butSend
            // 
            this.butSend.Location = new System.Drawing.Point(12, 12);
            this.butSend.Name = "butSend";
            this.butSend.Size = new System.Drawing.Size(108, 23);
            this.butSend.TabIndex = 1;
            this.butSend.Text = "Ustaw";
            this.butSend.UseVisualStyleBackColor = true;
            this.butSend.Click += new System.EventHandler(this.butSend_Click);
            // 
            // pbStatus
            // 
            this.pbStatus.BackColor = System.Drawing.Color.Red;
            this.pbStatus.Location = new System.Drawing.Point(12, 61);
            this.pbStatus.Name = "pbStatus";
            this.pbStatus.Size = new System.Drawing.Size(20, 20);
            this.pbStatus.TabIndex = 2;
            this.pbStatus.TabStop = false;
            this.pbStatus.Click += new System.EventHandler(this.pbStatus_Click);
            // 
            // labStatus
            // 
            this.labStatus.AccessibleDescription = "";
            this.labStatus.AccessibleName = "";
            this.labStatus.AutoSize = true;
            this.labStatus.Location = new System.Drawing.Point(178, 64);
            this.labStatus.Name = "labStatus";
            this.labStatus.Size = new System.Drawing.Size(109, 17);
            this.labStatus.TabIndex = 4;
            this.labStatus.Text = "Brak połączenia";
            this.labStatus.Click += new System.EventHandler(this.label1_Click);
            // 
            // numericSend
            // 
            this.numericSend.Location = new System.Drawing.Point(181, 13);
            this.numericSend.Maximum = new decimal(new int[] {
            1100,
            0,
            0,
            0});
            this.numericSend.Minimum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numericSend.Name = "numericSend";
            this.numericSend.ReadOnly = true;
            this.numericSend.Size = new System.Drawing.Size(106, 22);
            this.numericSend.TabIndex = 5;
            this.numericSend.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericSend.ValueChanged += new System.EventHandler(this.numericSend_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ClientSize = new System.Drawing.Size(329, 126);
            this.Controls.Add(this.numericSend);
            this.Controls.Add(this.labStatus);
            this.Controls.Add(this.pbStatus);
            this.Controls.Add(this.butSend);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Jasność świecenia";
            ((System.ComponentModel.ISupportInitialize)(this.pbStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericSend)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button butSend;
        private System.Windows.Forms.PictureBox pbStatus;
        private System.Windows.Forms.Label labStatus;
        private System.Windows.Forms.NumericUpDown numericSend;
    }
}

