import streamlit as st
import subprocess
import os

st.title("Extended MST: Nodes + Edges Weights")

num_nodes = st.number_input("Number of nodes", min_value=1, value=4)
num_edges = st.number_input("Number of edges", min_value=1, value=4)

node_weights_input = st.text_input("Node weights (space separated)", "3 2 4 1")
edges_input = st.text_area("Edges (u v edge_weight)", "1 2 5\n2 3 6\n3 4 2\n4 1 3", height=150)

if st.button("Compute MST"):
    node_weights_list = node_weights_input.strip().split()
    if len(node_weights_list) != num_nodes:
        st.error(f"Number of node weights ({len(node_weights_list)}) does not match number of nodes ({num_nodes})")
    else:
        input_lines = [f"{num_nodes} {num_edges}", node_weights_input.strip()] + edges_input.strip().splitlines()
        input_str = "\n".join(input_lines)

        if not os.path.exists("mst.c"):
            st.error("mst.c not found in the working directory.")
        else:
            compile_proc = subprocess.run(["gcc", "mst.c", "-o", "mst_exec"], capture_output=True, text=True)
            if compile_proc.returncode != 0:
                st.error(f"Compilation failed:\n{compile_proc.stderr}")
            else:
                try:
                    run_proc = subprocess.run(
                        ["./mst_exec"],
                        input=input_str,
                        capture_output=True,
                        text=True,
                        timeout=10
                    )
                    if run_proc.returncode != 0:
                        st.error(f"Execution failed:\n{run_proc.stderr}")
                    else:
                        st.success("MST Computed Successfully!")
                        st.code(run_proc.stdout.strip())
                except subprocess.TimeoutExpired:
                    st.error("Execution timed out.")
