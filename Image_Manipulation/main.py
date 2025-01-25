import tkinter as tk
import cv2 as cv
from PIL import Image, ImageTk
from tkinter import messagebox, filedialog
from Image_Color_Focuser import processImageFocus
from Image_Hue_Booster import hueBoostImage
import numpy as np

base_Image = None
target_Image = None
resized_Image = None
lastWindowW = -1
lastWindowH = -1

def setImageInLabel(updateImage = False):
    global resized_Image
    global lastWindowW, lastWindowH

    if target_Image is None:
        return

    if root.winfo_width() == lastWindowW and root.winfo_height() == lastWindowH and not updateImage:
        return

    lastWindowW = root.winfo_width()
    lastWindowH = root.winfo_height()

    new_size = (root.winfo_width(), root.winfo_height())
    resized_Image = target_Image.resize(new_size)
    tk_image = ImageTk.PhotoImage(resized_Image)

    image_label.config(image=tk_image, justify='center')
    image_label.image = tk_image  # Keep a reference to avoid garbage collection
    image_label.update_idletasks()

def imageReset():
    global target_Image
    target_Image = base_Image.copy()
    setImageInLabel(True)

def imageColorFocus(focusColor = 'red'):
    global target_Image
    cvImage = cv.cvtColor(np.array(target_Image), cv.COLOR_RGB2BGR)
    cvImage = processImageFocus(cvImage, focusColor)
    cvImage = cv.cvtColor(cvImage, cv.COLOR_BGR2RGB)
    target_Image = Image.fromarray(cvImage)
    setImageInLabel(True)

def imageHueBoost():
    global target_Image
    cvImage = cv.cvtColor(np.array(target_Image), cv.COLOR_RGB2BGR)
    cvImage = hueBoostImage(cvImage, '1')
    cvImage = cv.cvtColor(cvImage, cv.COLOR_BGR2RGB)
    target_Image = Image.fromarray(cvImage)
    setImageInLabel(True)

def pdfPrepare():
    global target_Image, updateImage
    pdf_canvas = Image.new("RGB", (595, 842), "white")
    img_width, img_height = target_Image.size
    x_offset = (595 - img_width) // 2
    y_offset = (842 - img_height) // 2
    pdf_canvas.paste(target_Image, (x_offset, 0))
    target_Image = pdf_canvas
    setImageInLabel(True)

def open_file_dialog():
    global base_Image, target_Image, updateImage
    file_path = filedialog.askopenfilename(
        title="Open a File",
        filetypes=(("Image files", ["*.jpg", "*.png", "*.jpeg"]), ("All files", "*.*"))
    )
    if file_path:
        base_Image = Image.open(file_path)
        target_Image = base_Image.copy()
        updateImage = True
        setImageInLabel()

def save_file_dialog():
    global target_Image
    file_path = filedialog.asksaveasfilename(
        title="Open a File",
        filetypes=(("Image", ".png"),("PDF", ".pdf")),
        defaultextension=".png"
    )
    if file_path:
        if file_path.endswith(".pdf"):
            target_Image.save(file_path, "PDF", save_all=True)
        else:
            print (file_path)
            target_Image.save(file_path)

def on_window_resize(arg):
    #image_label.place(width=image_label.winfo_screenwidth(), height=image_label.winfo_screenheight())
    pass

def update_label():
    setImageInLabel()
    root.after(10, update_label)  # Schedule the function again after 1 second

root = tk.Tk()
root.title("test window")
root.geometry("800x600")
root.bind("<Configure>", on_window_resize)

menu_bar = tk.Menu(root)
root.config(menu=menu_bar)

file_menu = tk.Menu(menu_bar, tearoff=0)
file_menu.add_command(label="Aç", command=open_file_dialog)
file_menu.add_command(label="Kaydet", command=save_file_dialog)
file_menu.add_separator()
file_menu.add_command(label="Çık", command=root.quit)

menu_bar.add_cascade(label="Dosya", menu=file_menu)

image_menu = tk.Menu(menu_bar, tearoff=0)
image_menu.add_command(label="Reset", command=imageReset)
image_menu.add_command(label="Kırmızı fokus", command=lambda: imageColorFocus('red'))
image_menu.add_command(label="Mavi fokus", command=lambda: imageColorFocus('blue'))
image_menu.add_command(label="Yeşil fokus", command=lambda: imageColorFocus('green'))
image_menu.add_command(label="Renk dolgunlaştır", command=lambda: imageHueBoost())
image_menu.add_command(label="Pdf hazırla", command=lambda: pdfPrepare())

menu_bar.add_cascade(label="Düzenle", menu=image_menu)

image_label = tk.Label(root)
image_label.pack(pady=20)

update_label()
root.mainloop()
