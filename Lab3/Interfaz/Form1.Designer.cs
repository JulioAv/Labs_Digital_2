
namespace Interfaz
{
    partial class Interfaz
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonEnviar = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textContador = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonEnviar
            // 
            this.buttonEnviar.Location = new System.Drawing.Point(210, 82);
            this.buttonEnviar.Name = "buttonEnviar";
            this.buttonEnviar.Size = new System.Drawing.Size(75, 31);
            this.buttonEnviar.TabIndex = 1;
            this.buttonEnviar.Text = "Enviar";
            this.buttonEnviar.UseVisualStyleBackColor = true;
            this.buttonEnviar.Click += new System.EventHandler(this.buttonEnviar_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textContador);
            this.groupBox1.Controls.Add(this.buttonEnviar);
            this.groupBox1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.groupBox1.Location = new System.Drawing.Point(40, 33);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(303, 232);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "PIC16F887";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // textContador
            // 
            this.textContador.Location = new System.Drawing.Point(57, 84);
            this.textContador.Name = "textContador";
            this.textContador.Size = new System.Drawing.Size(130, 29);
            this.textContador.TabIndex = 2;
            // 
            // Interfaz
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.ClientSize = new System.Drawing.Size(389, 314);
            this.Controls.Add(this.groupBox1);
            this.Name = "Interfaz";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button buttonEnviar;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textContador;
    }
}

