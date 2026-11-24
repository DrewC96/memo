using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Input;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Input;

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

        private void Canvas_PointerMoved(object sender, PointerRoutedEventArgs e)
        {
            // Filter specifically for Pen input
            if (e.Pointer.PointerDeviceType != PointerDeviceType.Pen)
                return;

            PointerPoint point = e.GetCurrentPoint((UIElement)sender);
            PointerPointProperties props = point.Properties;

            // 1. Coordinates & Pressure (normalized 0.0 to 1.0 across 4096 MPP 2.0 levels)
            double x = point.Position.X;
            double y = point.Position.Y;
            float pressure = props.Pressure;

            // 2. MPP 2.0 Tilt (-90 to +90 degrees)
            float tiltX = props.XTilt;
            float tiltY = props.YTilt;

            // 3. Buttons & Eraser
            bool isBarrelPressed = props.IsBarrelButtonPressed;
            bool isEraser = props.IsEraser;
            bool isInContact = point.IsInContact; // False when hovering
        }
    }
}
