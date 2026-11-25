using System;
using System.Collections.ObjectModel;
using System.Linq;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace Memo
{
    public sealed partial class HomePage : Page
    {
        public ObservableCollection<NotePage> RecentPages { get; } = new();

        public HomePage()
        {
            this.InitializeComponent();
            NotebookGrid.ItemsSource = AppData.Notebooks;

            var recent = AppData.Notebooks
                .SelectMany(n => n.Sections)
                .SelectMany(s => s.Pages)
                .OrderByDescending(p => p.LastModified)
                .Take(10);
            foreach (var p in recent) RecentPages.Add(p);
        }

        public static string FormatDate(DateTime d)
        {
            var age = DateTime.Now - d;
            if (age.TotalMinutes < 1) return "Just now";
            if (age.TotalHours < 1) return $"{(int)age.TotalMinutes}m ago";
            if (age.TotalDays < 1) return $"{(int)age.TotalHours}h ago";
            return d.ToString("MMM d");
        }

        public static string FormatSectionCount(int count) =>
            count == 1 ? "1 section" : $"{count} sections";

        private void NotebookGrid_ItemClick(object sender, ItemClickEventArgs e)
        {
            Frame.Navigate(typeof(NotebookPage), e.ClickedItem);
        }

        private void NewNotebook_Click(object sender, RoutedEventArgs e)
        {
            AppData.Notebooks.Add(new Notebook { Name = $"Notebook {AppData.Notebooks.Count + 1}" });
        }
    }

    public static class AppData
    {
        public static ObservableCollection<Notebook> Notebooks { get; } = new();
    }
}
