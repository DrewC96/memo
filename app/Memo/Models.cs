using System;
using System.Collections.ObjectModel;

namespace Memo
{
    public class NotePage
    {
        public Guid Id { get; } = Guid.NewGuid();
        public string Title { get; set; } = "Untitled page";
    }

    public class Section
    {
        public string Name { get; set; } = "New Section";
        public ObservableCollection<NotePage> Pages { get; } = new();
    }
}
