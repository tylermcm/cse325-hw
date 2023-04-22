using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyFirstConsoleApplication
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string name = "Tyler McMurtrey";
            string location = "Denver, Colorado";
            DateTime date = DateTime.Now;
            DateTime endDate = Convert.ToDateTime("12/25/2023");
            double totalDays = (endDate - date).TotalDays;

            Console.WriteLine("My name is {0}.", name);
            Console.WriteLine("I am from {0}.", location);
            Console.WriteLine(date.ToString("dd/MM/yyyy"));
            Console.WriteLine("There are {0} days until Christmas.", Math.Round(totalDays));

            double width, height, woodLength, glassArea;
            string widthString, heightString;
            Console.Write("Enter in the width: ");
            widthString = Console.ReadLine();
            width = double.Parse(widthString);
            Console.Write("Enter the height: ");
            heightString = Console.ReadLine();
            height = double.Parse(heightString);
            woodLength = 2 * (width + height) * 3.25;
            glassArea = 2 * (width * height);
            Console.WriteLine("The length of the wood is " +
            woodLength + " feet");
            Console.WriteLine("The area of the glass is " +
            glassArea + " square metres");

            Console.ReadKey();
        }
    }
}
