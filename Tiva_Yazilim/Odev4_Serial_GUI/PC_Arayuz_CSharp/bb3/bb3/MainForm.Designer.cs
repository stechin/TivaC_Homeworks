/*
 * Created by SharpDevelop.
 * User: ardayavuz
 * Date: 4.12.2025
 * Time: 14:53
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace bb3
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
			this.label1 = new System.Windows.Forms.Label();
			this.TextBoxPortNo = new System.Windows.Forms.TextBox();
			this.ButtonPortAc = new System.Windows.Forms.Button();
			this.ButtonPortKapat = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.TextBoxMetin = new System.Windows.Forms.TextBox();
			this.ButtonMetinGonder = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.TextBoxSaat = new System.Windows.Forms.TextBox();
			this.ButtonSaatGonder = new System.Windows.Forms.Button();
			this.TextBoxGelenSaat = new System.Windows.Forms.TextBox();
			this.TextBoxGelenADC = new System.Windows.Forms.TextBox();
			this.TextBoxGelenButon = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// serialPort1
			// 
			this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort1DataReceived);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(36, 27);
			this.label1.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(146, 52);
			this.label1.TabIndex = 0;
			this.label1.Text = "portno";
			// 
			// TextBoxPortNo
			// 
			this.TextBoxPortNo.Location = new System.Drawing.Point(238, 24);
			this.TextBoxPortNo.Name = "TextBoxPortNo";
			this.TextBoxPortNo.Size = new System.Drawing.Size(200, 53);
			this.TextBoxPortNo.TabIndex = 1;
			// 
			// ButtonPortAc
			// 
			this.ButtonPortAc.Location = new System.Drawing.Point(490, 30);
			this.ButtonPortAc.Name = "ButtonPortAc";
			this.ButtonPortAc.Size = new System.Drawing.Size(176, 52);
			this.ButtonPortAc.TabIndex = 2;
			this.ButtonPortAc.Text = "port aç";
			this.ButtonPortAc.UseVisualStyleBackColor = true;
			this.ButtonPortAc.Click += new System.EventHandler(this.ButtonPortAcClick);
			// 
			// ButtonPortKapat
			// 
			this.ButtonPortKapat.Location = new System.Drawing.Point(701, 27);
			this.ButtonPortKapat.Name = "ButtonPortKapat";
			this.ButtonPortKapat.Size = new System.Drawing.Size(168, 52);
			this.ButtonPortKapat.TabIndex = 3;
			this.ButtonPortKapat.Text = "KAPAT";
			this.ButtonPortKapat.UseVisualStyleBackColor = true;
			this.ButtonPortKapat.Click += new System.EventHandler(this.ButtonPortKapatClick);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(36, 165);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(171, 43);
			this.label2.TabIndex = 4;
			this.label2.Text = "text";
			// 
			// TextBoxMetin
			// 
			this.TextBoxMetin.Location = new System.Drawing.Point(238, 162);
			this.TextBoxMetin.Name = "TextBoxMetin";
			this.TextBoxMetin.Size = new System.Drawing.Size(200, 53);
			this.TextBoxMetin.TabIndex = 5;
			// 
			// ButtonMetinGonder
			// 
			this.ButtonMetinGonder.Location = new System.Drawing.Point(490, 167);
			this.ButtonMetinGonder.Name = "ButtonMetinGonder";
			this.ButtonMetinGonder.Size = new System.Drawing.Size(176, 51);
			this.ButtonMetinGonder.TabIndex = 6;
			this.ButtonMetinGonder.Text = "Gönder";
			this.ButtonMetinGonder.UseVisualStyleBackColor = true;
			this.ButtonMetinGonder.Click += new System.EventHandler(this.ButtonMetinGonderClick);
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(36, 260);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(196, 43);
			this.label3.TabIndex = 7;
			this.label3.Text = "hh:mm:ss";
			// 
			// TextBoxSaat
			// 
			this.TextBoxSaat.Location = new System.Drawing.Point(238, 250);
			this.TextBoxSaat.Name = "TextBoxSaat";
			this.TextBoxSaat.Size = new System.Drawing.Size(200, 53);
			this.TextBoxSaat.TabIndex = 8;
			// 
			// ButtonSaatGonder
			// 
			this.ButtonSaatGonder.Location = new System.Drawing.Point(490, 250);
			this.ButtonSaatGonder.Name = "ButtonSaatGonder";
			this.ButtonSaatGonder.Size = new System.Drawing.Size(176, 51);
			this.ButtonSaatGonder.TabIndex = 9;
			this.ButtonSaatGonder.Text = "Gönder";
			this.ButtonSaatGonder.UseVisualStyleBackColor = true;
			this.ButtonSaatGonder.Click += new System.EventHandler(this.ButtonSaatGonderClick);
			// 
			// TextBoxGelenSaat
			// 
			this.TextBoxGelenSaat.Location = new System.Drawing.Point(36, 391);
			this.TextBoxGelenSaat.Name = "TextBoxGelenSaat";
			this.TextBoxGelenSaat.Size = new System.Drawing.Size(200, 53);
			this.TextBoxGelenSaat.TabIndex = 10;
			// 
			// TextBoxGelenADC
			// 
			this.TextBoxGelenADC.Location = new System.Drawing.Point(306, 391);
			this.TextBoxGelenADC.Name = "TextBoxGelenADC";
			this.TextBoxGelenADC.Size = new System.Drawing.Size(200, 53);
			this.TextBoxGelenADC.TabIndex = 11;
			// 
			// TextBoxGelenButon
			// 
			this.TextBoxGelenButon.Location = new System.Drawing.Point(594, 391);
			this.TextBoxGelenButon.Name = "TextBoxGelenButon";
			this.TextBoxGelenButon.Size = new System.Drawing.Size(200, 53);
			this.TextBoxGelenButon.TabIndex = 12;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(23F, 46F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(892, 483);
			this.Controls.Add(this.TextBoxGelenButon);
			this.Controls.Add(this.TextBoxGelenADC);
			this.Controls.Add(this.TextBoxGelenSaat);
			this.Controls.Add(this.ButtonSaatGonder);
			this.Controls.Add(this.TextBoxSaat);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.ButtonMetinGonder);
			this.Controls.Add(this.TextBoxMetin);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.ButtonPortKapat);
			this.Controls.Add(this.ButtonPortAc);
			this.Controls.Add(this.TextBoxPortNo);
			this.Controls.Add(this.label1);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
			this.Margin = new System.Windows.Forms.Padding(10, 9, 10, 9);
			this.Name = "MainForm";
			this.Text = "bb3";
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.TextBox TextBoxGelenButon;
		private System.Windows.Forms.TextBox TextBoxGelenADC;
		private System.Windows.Forms.TextBox TextBoxGelenSaat;
		private System.Windows.Forms.Button ButtonSaatGonder;
		private System.Windows.Forms.TextBox TextBoxSaat;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button ButtonMetinGonder;
		private System.Windows.Forms.TextBox TextBoxMetin;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button ButtonPortKapat;
		private System.Windows.Forms.Button ButtonPortAc;
		private System.Windows.Forms.TextBox TextBoxPortNo;
		private System.Windows.Forms.Label label1;
		private System.IO.Ports.SerialPort serialPort1;
	}
}
