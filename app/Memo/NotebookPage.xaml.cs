using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;

namespace Memo
{
    public sealed partial class NotebookPage : Page
    {
        private Notebook? notebook;

        public NotebookPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            notebook = (Notebook)e.Parameter;
            NotebookTitle.Text = notebook.Name;
            SectionList.ItemsSource = notebook.Sections;

            if (notebook.Sections.Count == 0)
                AddSection_Click(this, null!);
            else
                SectionList.SelectedIndex = 0;
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            if (Frame.CanGoBack) Frame.GoBack();
        }

        private void AddSection_Click(object sender, RoutedEventArgs e)
        {
            if (notebook is null) return;
            var section = new Section { Name = $"Section {notebook.Sections.Count + 1}" };
            section.Pages.Add(new NotePage());
            notebook.Sections.Add(section);
            SectionList.SelectedItem = section;
        }

        private void SectionList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var section = SectionList.SelectedItem as Section;
            PageList.ItemsSource = section?.Pages;
            PageList.SelectedIndex = (section?.Pages.Count ?? 0) > 0 ? 0 : -1;
        }

        private void AddPage_Click(object sender, RoutedEventArgs e)
        {
            if (SectionList.SelectedItem is not Section section) return;
            var page = new NotePage { Title = $"Page {section.Pages.Count + 1}" };
            section.Pages.Add(page);
            PageList.SelectedItem = page;
        }

        private void PageList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // later: save the page in e.RemovedItems before switching
            NoteCanvasControl.ShowPage(PageList.SelectedItem as NotePage);
        }
    }
}
