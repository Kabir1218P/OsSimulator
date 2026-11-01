# OS Simulator (Memory Management & CPU Scheduling)

An interactive Operating Systems simulation tool and lab suite featuring a Flask-based web application to simulate and visualize memory allocation and paging policies, alongside C implementations of CPU scheduling algorithms.

---

## 🚀 Features

### 1. Memory Allocation Simulator
- Visualizes contiguous memory allocation strategies:
  - **First Fit**: Allocates the first available hole large enough to accommodate the process.
  - **Best Fit**: Allocates the smallest available hole that fits the process to minimize leftover space.
  - **Worst Fit**: Allocates the largest available hole.
- Custom memory sizes and customizable process queues (JSON format).

### 2. Page Replacement Simulator
- Simulates virtual memory page replacement policies:
  - **FIFO** (First-In, First-Out)
  - **LRU** (Least Recently Used)
  - **Optimal** (Replaces the page not used for the longest period in the future)
- Customizable frame count and reference string sequence.
- Tracks page hits, page faults, and frame timeline states.

### 3. CPU Priority Scheduling (`test.c`)
- Standalone C console utility for CPU scheduling:
  - **Non-Preemptive Priority Scheduling**
  - **Preemptive Priority Scheduling**
- Computes Arrival Time (AT), Burst Time (BT), Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Visualizes execution order via a generated Gantt chart.

---

## 📁 Project Structure

```text
.
├── app.py              # Flask server and API endpoints (/simulate_allocation, /simulate_paging)
├── algorithms.py       # Paging & memory management logic (FIFO, LRU, Optimal)
├── test.c              # C program implementing Preemptive and Non-Preemptive Priority Scheduling
├── templates/          # HTML templates
│   ├── index.html      # Landing page
│   ├── simulate.html   # Simulator interface
│   └── results.html    # Results display
├── static/             # Frontend assets
│   ├── script.js       # Client-side API caller & DOM handler
│   └── style.css       # Styling
├── requirements.txt    # Python dependencies
└── README.md           # Project documentation
```

---

## 🛠️ Getting Started

### Prerequisites
- **Python 3.8+**
- **GCC / Clang** (optional, for compiling the C scheduling program)

### 1. Setup & Run the Web Simulator

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Kabir1218P/OsSimulator.git
   cd OsSimulator
   ```

2. **Install dependencies:**
   ```bash
   pip install -r requirements.txt
   ```

3. **Start the Flask server:**
   ```bash
   python app.py
   ```

4. **Access the simulator:**
   Open your browser and navigate to:
   ```
   http://127.0.0.1:5000
   ```
   Or visit `http://127.0.0.1:5000/ui` directly to test memory allocation and page replacement.

---

### 2. Run the CPU Scheduling Program (C)

1. **Compile `test.c`:**
   ```bash
   gcc test.c -o scheduler
   ```

2. **Run the executable:**
   ```bash
   ./scheduler
   ```

3. Follow the interactive CLI prompts to enter the number of processes, arrival times, burst times, and priorities.
