using System;
using System.Collections.ObjectModel;

namespace Memo
{
    public class NotePage
    {
        public Guid Id { get; } = Guid.NewGuid();
        public string Title { get; set; } = "Untitled page";
        public DateTime LastModified { get; set; } = DateTime.Now;
    }

    public class Section
    {
        public string Name { get; set; } = "New Section";
        public ObservableCollection<NotePage> Pages { get; } = new();
    }

    public class Notebook
    {
        public string Name { get; set; } = "New Notebook";
        public ObservableCollection<Section> Sections { get; } = new();
    }
}
