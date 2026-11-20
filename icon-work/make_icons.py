from PIL import Image

SRC = "icon_source.png"   # your big notebook icon
OUT = r"C:\Dev\Memo\app\Memo\Assets"

# name: (width, height)
targets = {
    "Square44x44Logo.targetsize-24_altform-unplated.png": (24, 24),
    "Square44x44Logo.targetsize-48_altform-lightunplated.png": (48, 48),
    "Square44x44Logo.scale-200.png": (88, 88),
    "Square150x150Logo.scale-200.png": (300, 300),
    "Wide310x150Logo.scale-200.png": (620, 300),
    "SplashScreen.scale-200.png": (1240, 600),
    "LockScreenLogo.scale-200.png": (48, 48),
    "StoreLogo.png": (50, 50),
}

src = Image.open(SRC).convert("RGBA")

for name, (w, h) in targets.items():
    canvas = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    # fit the icon inside with a little padding, centered
    s = int(min(w, h) * 0.8) if (w, h) != (24, 24) else 24
    icon = src.resize((s, s), Image.LANCZOS)
    canvas.paste(icon, ((w - s) // 2, (h - s) // 2), icon)
    canvas.save(f"{OUT}\\{name}")
