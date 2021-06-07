using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO.Ports;

namespace regulacja_swiatla
{
    public partial class Form1 : Form
    {
       // zmienna od portu
        SerialPort port;
        public Form1()
        {
            InitializeComponent();

            //inicjalizacja zmiennej port z domyślnymi wartościami 
            port = new SerialPort();
            //ustawienie timeoutów aby program się nie wieszał 
            port.ReadTimeout = 500;
            port.WriteTimeout = 500;

        }


        private void butSend_Click(object sender, EventArgs e)
        {
            if (port.IsOpen)
            {
                string do_wyslania = numericSend.Value.ToString();
                
                if (do_wyslania.Length == 1)
                {
                    do_wyslania = "000" + do_wyslania; 
                }
                if (do_wyslania.Length ==2)
                {
                    do_wyslania = "00" + do_wyslania; 
                }
                if(do_wyslania.Length == 3)
                {
                    do_wyslania = "0" + do_wyslania;
                }
                port.Write(do_wyslania);
            }
            else System.Windows.Forms.MessageBox.Show("Niepołączono z urządzeniem");
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void pbStatus_Click(object sender, EventArgs e)
        {
            //jeżeli połączenie jest aktywne to je kończymy, zmieniamy kolor na red i zmieniamy napis 
            if (port.IsOpen)
            {
                pbStatus.BackColor = System.Drawing.Color.Red;
                port.Close();
                labStatus.Text = "Brak połączenia";
                
            }
            //w przeciwnym wypadku włączamy połączenie, zmieniamy kolor na zielony i zmieniamy napis 
            else
            {
                //połączenie może nie być możliwe dlatego należy się zabezpieczyć na wypadek błędu 
                try
                {
                    //najpierw przepisujemy do portu parametry
                    port.PortName = "COM3";
                    port.BaudRate = Int32.Parse("9600");
                    port.DataBits = Int32.Parse("8");
                    port.Parity = (Parity)Enum.Parse(typeof(Parity), "None");
                    port.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "One");
                    //a następnie uruchamiamy port 
                    port.Open();
                    //po uruchomieniu zmieniamy elementy graficzne interfejsu 
                    pbStatus.BackColor = System.Drawing.Color.Green;
                    labStatus.Text = "Aktywne połączenie";
                    
                }
                
                catch (Exception exc)
                {
                    MessageBox.Show("Błąd połączenia:\n" + exc.Message);
                }
            }
        }

        private void numericSend_ValueChanged(object sender, EventArgs e)
        {
            
        }
    }
}
