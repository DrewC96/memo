using Microsoft.UI.Xaml.Controls;

namespace Memo
{
    public sealed partial class NoteCanvas : UserControl
    {
        public NoteCanvas()
        {
            this.InitializeComponent();
        }

        public void ShowPage(NotePage? page)
        {
            Label.Text = page?.Title ?? "No page selected";
            // later: ask the engine to load strokes for page.Id
        }
    }
}
