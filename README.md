# Unreal Performance Monitor
A lightweight, no-nonsense performance monitoring plugin for Unreal Engine 5. 
It provides a quick, real-time overview of your game's vital performance metrics without cluttering your screen.

<img src="UnrealPerfMonDemo/Plugins/UnrealPerformanceMonitor/Resources/Icon128.png">

## Features

* **Lightweight & Fast:** Minimal CPU/GPU overhead.
* **Essential Metrics:** Displays FPS, Frame Time (ms), Memory Usage, and active GPU Name.
* **Dual Display Options:** Toggle via a quick Console Command or integrate it directly into your UI using a Widget Blueprint.

---

## How to Use

### 1. Console Command (CVar)
The quickest way to check performance on the fly is using the built-in Console Variable. Open the UE5 console (`` ` `` key) and type:

* **Show Stats:** `PerformanceMonitor.ShowStats 1`
* **Hide Stats:** `PerformanceMonitor.ShowStats 0`

### 2. Widget Blueprint
For custom UI layouts or shipping builds where the console is disabled:
1. Search for `WBP_PerformanceWidget` in the plugin's Content folder.
2. Add it to your viewport via your HUD or Player Controller Blueprint using the **Create Widget** and **Add to Viewport** nodes.

---

## Metrics Tracked

| Metric | Description |
| :--- | :--- |
| **FPS** | Frames per second, smoothed over recent frames. |
| **Frame Time** | Total time taken to render a single frame (in milliseconds). |
| **Physical Memory Usage** | Current physical memory (RAM) allocated by the application. |
| **Virtual Memory Usage** | Current virtual memory (RAM) allocated by the application. |
| **GPU Name** | The specific graphics card currently driving the engine viewport. |

---

## Installation

1. Download or clone this repository.
2. Copy the `UnrealPerformanceMonitor` folder into your project's `Plugins` directory (create one in your project root if it doesn't exist).
3. Restart Unreal Engine 5.
4. Go to **Edit > Plugins** and ensure **Unreal Performance Monitor** is enabled.
