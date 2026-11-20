using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System.Collections.ObjectModel;

namespace Memo
{
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
            this.ExtendsContentIntoTitleBar = true;
            this.SetTitleBar(CustomTitleBar);

            this.AppWindow.SetIcon("Assets/AppIcon.ico");   // from the template; delete if it errors

            this.AppWindow.Closing += AppWindow_Closing;
            InitializeApplication();
        }

        private void InitializeApplication()
        {
            // TODO: create the native engine here once MemoEngine exists
        }

        private void Root_Loaded(object sender, RoutedEventArgs e)
        {
            // TODO: load initial document
            if (Sections.Count == 0)
                AddSection_Click(this, null!);
        }

        private void AppWindow_Closing(AppWindow sender, AppWindowClosingEventArgs args)
        {
            // TODO: save state, dispose engine
        }
        public ObservableCollection<Section> Sections { get; } = new();

        private void AddSection_Click(object sender, RoutedEventArgs e)
        {
            var section = new Section { Name = $"Section {Sections.Count + 1}" };
            section.Pages.Add(new NotePage());
            Sections.Add(section);
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
