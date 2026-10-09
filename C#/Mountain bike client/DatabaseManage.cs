using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1
{

    public partial class DatabaseManage: Form
    {

        string connectionString = "Data Source=MIHAI;Initial Catalog=Mountain bike racing;Integrated Security=True;TrustServerCertificate=True";

        SqlDataAdapter ParentDataAdapter = new SqlDataAdapter();
        SqlDataAdapter ChildDataAdapter = new SqlDataAdapter();

        BindingSource ParentBindingSource = new BindingSource();
        BindingSource ChildBindingSource = new BindingSource();

        SqlCommandBuilder ParentBuilder = new SqlCommandBuilder();
        SqlCommandBuilder ChildBuilder = new SqlCommandBuilder();

        DataSet dataSet = new DataSet();

        public static string ParentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        public static string ChildTableName = ConfigurationManager.AppSettings["ChildTableName"];
        public static string ChildColumnNames = ConfigurationManager.AppSettings["ChildColumnNames"];
        public static string ColumnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
        public static string ChildFK = ConfigurationManager.AppSettings["ChildFK"];
        public static string ChildPK = ConfigurationManager.AppSettings["ChildPK"];
        public static string ParentPK = ConfigurationManager.AppSettings["ParentPK"];
        public static string ChildDeleteQuery = ConfigurationManager.AppSettings["DeleteQuery"];

        public DatabaseManage()
        {
            InitializeComponent();
            loadAllBikers();
        }

        private void loadAllBikers()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                string selectQuery = $"SELECT * FROM {ParentTableName}";

                ParentDataAdapter.SelectCommand = new SqlCommand(selectQuery, conn);
                ParentBuilder.DataAdapter = ParentDataAdapter;

                if (dataSet.Tables.Contains(ParentTableName))
                    dataSet.Tables[ParentTableName].Clear();

                ParentDataAdapter.Fill(dataSet, ParentTableName);

                ParentBindingSource.DataSource = dataSet.Tables[ParentTableName];
                bikersView.DataSource = ParentBindingSource;

                conn.Close();
            }
        }



        private void bikersView_SelectionChanged(object sender, EventArgs e)
        {
            if (bikersView.CurrentRow == null)
                return;

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                int parentId = Convert.ToInt32(bikersView.CurrentRow.Cells[ParentPK].Value);
                string selectQuery = $"SELECT {ChildColumnNames} FROM {ChildTableName} WHERE {ChildFK} = @parentId";

                ChildDataAdapter.SelectCommand = new SqlCommand(selectQuery, conn);
                ChildDataAdapter.SelectCommand.Parameters.AddWithValue("@parentId", parentId);
                ChildBuilder.DataAdapter = ChildDataAdapter;

                if (dataSet.Tables.Contains(ChildTableName))
                    dataSet.Tables[ChildTableName].Clear();

                ChildDataAdapter.Fill(dataSet, ChildTableName);

                ChildBindingSource.DataSource = dataSet.Tables[ChildTableName];
                bikesView.DataSource = ChildBindingSource;

                conn.Close();
            }
        }

        private void addBikeButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(bikeSeries.Text))
                {
                    MessageBox.Show("Bike series missing!");
                    bikeSeries.Focus();
                    return;
                }

                if (string.IsNullOrWhiteSpace(bikeModel.Text))
                {
                    MessageBox.Show("Bike model missing!");
                    bikeModel.Focus();
                    return;
                }

                if (!int.TryParse(bikeValue.Text, out int value) || value <= 0)
                {
                    MessageBox.Show("Bike value must be a positive integer!");
                    bikeValue.Focus();
                    return;
                }

                if (bikersView.CurrentRow == null)
                {
                    MessageBox.Show("You didn't selected a biker for which you assign the bike!");
                    return;
                }

                int parentId = Convert.ToInt32(bikersView.CurrentRow.Cells[ParentPK].Value);

                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();

                    string sql = $@"
                INSERT INTO {ChildTableName} 
                    ({ChildColumnNames}) 
                VALUES 
                    ({ColumnNamesInsertParameters})";

                    SqlCommand cmd = new SqlCommand(sql, conn);

                    cmd.Parameters.AddWithValue("@BikeSeries", bikeSeries.Text.Trim());
                    cmd.Parameters.AddWithValue("@Model", bikeModel.Text.Trim());
                    cmd.Parameters.AddWithValue("@Value", value);
                    cmd.Parameters.AddWithValue("@BikerId", parentId);

                    int rowsAffected = cmd.ExecuteNonQuery();

                    if (rowsAffected > 0)
                    {
                        bikersView_SelectionChanged(null, null);

                        bikeSeries.Text = "";
                        bikeModel.Text = "";
                        bikeValue.Text = "";

                        MessageBox.Show("Bike added successfully!");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error: {ex.Message}");
            }
        }



        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();

                    string selectQuery = $"SELECT * FROM {ChildTableName}";
                    ChildDataAdapter.SelectCommand = new SqlCommand(selectQuery, conn);
                    ChildBuilder.DataAdapter = ChildDataAdapter;

                    DataTable dt = (DataTable)ChildBindingSource.DataSource;

                    ChildDataAdapter.Update(dt);

                    MessageBox.Show("Table data modified successfully!");

                    conn.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }


        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (bikesView.CurrentRow == null)
            {
                MessageBox.Show("No bike selected!");
                return;
            }

            var confirm = MessageBox.Show("Are you sure?",
                                          "Confirm",
                                          MessageBoxButtons.YesNo,
                                          MessageBoxIcon.Warning);
            if (confirm != DialogResult.Yes)
                return;

            var parentPkValue = bikesView.CurrentRow.Cells[ChildPK].Value;

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                string deleteMaintenances = $"DELETE FROM BikeMaintenance WHERE {ChildPK}=@ChildPK";
                using (SqlCommand cmd = new SqlCommand(deleteMaintenances, conn))
                {
                    cmd.Parameters.AddWithValue("@ChildPK", parentPkValue);
                    cmd.ExecuteNonQuery();
                }

                SqlCommand cmdDeleteBike = new SqlCommand(ChildDeleteQuery, conn);
                cmdDeleteBike.Parameters.AddWithValue($"@{ChildPK}", parentPkValue);

                int rows = cmdDeleteBike.ExecuteNonQuery();
                bikersView_SelectionChanged(null, null);
            }
        }




    }
}
